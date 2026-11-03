#include "CarePulseModules.h"
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cstdint>
#include <random>

string severityName(int s)
{
    if (s == 4)
        return "Critical";

    if (s == 3)
        return "Severe";

    if (s == 2)
        return "Moderate";

    return "Stable";
}

uint32_t cp_rotr(uint32_t x, uint32_t n)
{
    return (x >> n) | (x << (32 - n));
}

string cp_sha256(const string& input)
{
    static const uint32_t k[64] =
    {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
        0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
        0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
        0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    string msg = input;

    uint64_t bits = (uint64_t)msg.size() * 8;

    msg.push_back((char)0x80);

    while (msg.size() % 64 != 56)
    {
        msg.push_back(0);
    }

    for (int i = 7; i >= 0; --i)
    {
        msg.push_back((char)(bits >> (i * 8)));
    }

    uint32_t h[8] =
    {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    for (size_t off = 0; off < msg.size(); off += 64)
    {
        uint32_t w[64];

        for (int i = 0; i < 16; i++)
        {
            size_t j = off + 4 * i;

            w[i] =
                ((uint32_t)(unsigned char)msg[j] << 24) |
                ((uint32_t)(unsigned char)msg[j + 1] << 16) |
                ((uint32_t)(unsigned char)msg[j + 2] << 8) |
                (uint32_t)(unsigned char)msg[j + 3];
        }

        for (int i = 16; i < 64; i++)
        {
            uint32_t s0 =
                cp_rotr(w[i - 15], 7) ^
                cp_rotr(w[i - 15], 18) ^
                (w[i - 15] >> 3);

            uint32_t s1 =
                cp_rotr(w[i - 2], 17) ^
                cp_rotr(w[i - 2], 19) ^
                (w[i - 2] >> 10);

            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }

        uint32_t a = h[0];
        uint32_t b = h[1];
        uint32_t c = h[2];
        uint32_t d = h[3];
        uint32_t e = h[4];
        uint32_t f = h[5];
        uint32_t g = h[6];
        uint32_t z = h[7];

        for (int i = 0; i < 64; i++)
        {
            uint32_t s1 =
                cp_rotr(e, 6) ^
                cp_rotr(e, 11) ^
                cp_rotr(e, 25);

            uint32_t ch = (e & f) ^ ((~e) & g);

            uint32_t t1 = z + s1 + ch + k[i] + w[i];

            uint32_t s0 =
                cp_rotr(a, 2) ^
                cp_rotr(a, 13) ^
                cp_rotr(a, 22);

            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);

            uint32_t t2 = s0 + maj;

            z = g;
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t2;
        }

        h[0] += a;
        h[1] += b;
        h[2] += c;
        h[3] += d;
        h[4] += e;
        h[5] += f;
        h[6] += g;
        h[7] += z;
    }

    stringstream out;

    out << hex << setfill('0');

    for (int i = 0; i < 8; i++)
    {
        out << setw(8) << h[i];
    }

    return out.str();
}

string makeSalt()
{
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dist(0, 15);

    const char* h = "0123456789abcdef";

    string s;

    for (int i = 0; i < 32; i++)
    {
        s += h[dist(gen)];
    }

    return s;
}

string passwordDigest(const string& salt, const string& password)
{
    string v = salt + password;

    for (int i = 0; i < 5000; i++)
    {
        v = cp_sha256(v + salt + password);
    }

    return v;
}

bool validPassword(const string& p)
{
    bool u = false, l = false, n = false;

    for (size_t i = 0; i < p.size(); i++)
    {
        if (p[i] >= 'A' && p[i] <= 'Z')
            u = true;

        if (p[i] >= 'a' && p[i] <= 'z')
            l = true;

        if (p[i] >= '0' && p[i] <= '9')
            n = true;
    }

    return p.size() >= 8 && u && l && n;
}
