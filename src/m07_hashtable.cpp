#include "CarePulseModules.h"

class DoctorHashTable
{
    struct Node
    {
        int id, index;
        Node* next;

        Node(int a, int b, Node* n) : id(a), index(b), next(n)
        {
        }
    };

    Node* table[101];

    int hash(int id) const
    {
        return id % 101;
    }

public:
    DoctorHashTable()
    {
        for (int i = 0; i < 101; i++)
        {
            table[i] = NULL;
        }
    }

    ~DoctorHashTable()
    {
        clear();
    }

    void clear()
    {
        for (int i = 0; i < 101; i++)
        {
        while (table[i])
            {
                Node* t = table[i];
                table[i] = table[i]->next;
                delete t;
            }
        }
    }

    void reset(const HospitalData& d)
    {
        clear();

        for (int i = 0; i < d.doctorCount; i++)
        {
            int h = hash(d.doctors[i].id);

            table[h] = new Node(
                d.doctors[i].id,
                i,
                table[h]
            );
        }
    }

    int find(int id) const
    {
        for (Node* n = table[hash(id)]; n; n = n->next)
        {
            if (n->id == id)
            {
                return n->index;
            }
        }

        return -1;
    }
};

static DoctorHashTable doctorTable;

void hashRebuild(const HospitalData& d)
{
    doctorTable.reset(d);
}

int hashDoctorIndex(int id)
{
    return doctorTable.find(id);
}

void addDoctor(HospitalData& d, const string& user)
{
    if (d.doctorCount >= MAX_RECORDS)
    {
        cout << "Doctor list is full.\n";
        return;
    }

    Doctor x;

    cout << "Doctor ID: ";
    cin >> x.id;

    if (x.id <= 0 || findDoctorIndex(d, x.id) >= 0)
    {
        cout << "Invalid or duplicate doctor ID.\n";
        return;
    }

    cout << "Doctor name: ";
    getline(cin >> ws, x.name);

    cout << "Specialization: ";
    getline(cin >> ws, x.specialization);

    pushUndo(d, "Add doctor");

    d.doctors[d.doctorCount++] = x;

    hashRebuild(d);
    saveAll(d);

    auditAction(
        user,
        "Staff",
        "Added doctor ID " + to_string(x.id)
    );

    cout << "Doctor added.\n";
}
