#include "CarePulseModules.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

static string safe(string s)
{
    for (size_t i = 0; i < s.size(); i++)
    {
        if (s[i] == '|')
            s[i] = '/';
    }
    return s;
}

void auditAction(const string& user, const string& role, const string& action)
{
    ofstream f("audit.log", ios::app);

    if (f)
    {
        time_t now = time(NULL);
        tm *t = localtime(&now);
        char stamp[32];

        strftime(stamp, sizeof(stamp), "%Y-%m-%d %H:%M:%S", t);

        f << stamp << " | " << user << " | " << role << " | "
          << action << '\n';
    }
}

void saveAll(const HospitalData& d)
{
    ofstream f("patients.txt.tmp");

    for (int i = 0; i < d.patientCount; i++)
    {
        const Patient& p = d.patients[i];

        f << p.id << '|' << safe(p.name) << '|' << p.age << '|'
          << safe(p.diagnosis) << '|' << p.severity << '|'
          << p.doctorID << '|' << p.status << '|' << p.bedID << '|'
          << p.admitted << '|' << p.queueOrder << '|'
          << p.emergencyOrder << '\n';
    }

    f.close();
    remove("patients.txt");
    rename("patients.txt.tmp", "patients.txt");

    f.open("doctors.txt.tmp");

    for (int i = 0; i < d.doctorCount; i++)
    {
        f << d.doctors[i].id << '|'
          << safe(d.doctors[i].name) << '|'
          << d.doctors[i].age << '|'
          << safe(d.doctors[i].specialization) << '\n';
    }

    f.close();
    remove("doctors.txt");
    rename("doctors.txt.tmp", "doctors.txt");

    f.open("beds.txt.tmp");

    for (int i = 0; i < d.bedCount; i++)
    {
        f << d.beds[i].id << '|'
          << d.beds[i].roomID << '|'
          << safe(d.beds[i].roomType) << '|'
          << d.beds[i].occupied << '|'
          << d.beds[i].patientID << '\n';
    }

    f.close();
    remove("beds.txt");
    rename("beds.txt.tmp", "beds.txt");

    f.open("appointments.txt.tmp");

    for (int i = 0; i < d.appointmentCount; i++)
    {
        f << d.appointments[i].patientID << '|'
          << d.appointments[i].date << '|'
          << d.appointments[i].time << '|'
          << safe(d.appointments[i].note) << '\n';
    }

    f.close();
    remove("appointments.txt");
    rename("appointments.txt.tmp", "appointments.txt");

    f.open("bills.txt.tmp");

    for (int i = 0; i < d.billCount; i++)
    {
        f << d.bills[i].patientID << '|'
          << d.bills[i].subtotal << '|'
          << d.bills[i].tax << '|'
          << d.bills[i].total << '|'
          << safe(d.bills[i].description) << '\n';
    }

    f.close();
    remove("bills.txt");
    rename("bills.txt.tmp", "bills.txt");

    f.open("users.txt.tmp");

    for (int i = 0; i < d.userCount; i++)
    {
        f << d.users[i].username << '|'
          << d.users[i].salt << '|'
          << d.users[i].passwordHash << '|'
          << d.users[i].role << '\n';
    }

    f.close();
    remove("users.txt");
    rename("users.txt.tmp", "users.txt");

    f.open("settings.txt.tmp");

    f << d.nextArrival << ' ' << d.averageConsultMinutes << '\n';

    f.close();
    remove("settings.txt");
    rename("settings.txt.tmp", "settings.txt");
}

static int splitLine(const string& line, string out[], int max)
{
    int n = 0;
    string part;

    for (size_t i = 0; i < line.size(); i++)
    {
        if (line[i] == '|')
        {
            if (n < max)
                out[n++] = part;

            part.clear();
        }
        else
        {
            part += line[i];
        }
    }

    if (n < max)
        out[n++] = part;

    return n;
}

void loadAll(HospitalData& d)
{
    d = HospitalData();

    string line, p[12];
    ifstream f("patients.txt");

    while (getline(f, line) && d.patientCount < MAX_RECORDS)
    {
        if (splitLine(line, p, 12) >= 11)
        {
            Patient x;

            x.id = atoi(p[0].c_str());
            x.name = p[1];
            x.age = atoi(p[2].c_str());
            x.diagnosis = p[3];
            x.severity = atoi(p[4].c_str());
            x.doctorID = atoi(p[5].c_str());
            x.status = p[6];
            x.bedID = atoi(p[7].c_str());
            x.admitted = atoi(p[8].c_str()) != 0;
            x.queueOrder = atoi(p[9].c_str());
            x.emergencyOrder = atoi(p[10].c_str());

            d.patients[d.patientCount++] = x;
        }
    }

    f.close();
    f.open("doctors.txt");

    while (getline(f, line) && d.doctorCount < MAX_RECORDS)
    {
        if (splitLine(line, p, 12) >= 4)
        {
            Doctor x;

            x.id = atoi(p[0].c_str());
            x.name = p[1];
            x.age = atoi(p[2].c_str());
            x.specialization = p[3];

            d.doctors[d.doctorCount++] = x;
        }
    }

    f.close();
    f.open("beds.txt");

    while (getline(f, line) && d.bedCount < MAX_RECORDS)
    {
        if (splitLine(line, p, 12) >= 5)
        {
            Bed x;

            x.id = atoi(p[0].c_str());
            x.roomID = atoi(p[1].c_str());
            x.roomType = p[2];
            x.occupied = atoi(p[3].c_str()) != 0;
            x.patientID = atoi(p[4].c_str());

            d.beds[d.bedCount++] = x;
        }
    }

    f.close();
    f.open("appointments.txt");

    while (getline(f, line) && d.appointmentCount < MAX_RECORDS)
    {
        if (splitLine(line, p, 12) >= 4)
        {
            Appointment x;

            x.patientID = atoi(p[0].c_str());
            x.date = p[1];
            x.time = p[2];
            x.note = p[3];

            d.appointments[d.appointmentCount++] = x;
        }
    }

    f.close();
    f.open("bills.txt");

    while (getline(f, line) && d.billCount < MAX_RECORDS)
    {
        if (splitLine(line, p, 12) >= 5)
        {
            Bill x;

            x.patientID = atoi(p[0].c_str());
            x.subtotal = atof(p[1].c_str());
            x.tax = atof(p[2].c_str());
            x.total = atof(p[3].c_str());
            x.description = p[4];

            d.bills[d.billCount++] = x;
        }
    }

    f.close();
    f.open("users.txt");

    while (getline(f, line) && d.userCount < MAX_RECORDS)
    {
        if (splitLine(line, p, 12) >= 4)
        {
            User x;

            x.username = p[0];
            x.salt = p[1];
            x.passwordHash = p[2];
            x.role = p[3];

            d.users[d.userCount++] = x;
        }
    }

    f.close();
    f.open("settings.txt");

    if (f)
        f >> d.nextArrival >> d.averageConsultMinutes;

    f.close();

    if (d.nextArrival < 1)
        d.nextArrival = 1;

    if (d.averageConsultMinutes < 1 || d.averageConsultMinutes > 240)
        d.averageConsultMinutes = 15;

    rebuildStructures(d);
}

void rebuildStructures(const HospitalData& d)
{
    linkedListRebuild(d);
    opdRebuild(d);
    emergencyRebuild(d);
    bstRebuild(d);
    hashRebuild(d);
}
