#include "CarePulseModules.h"
#include <ctime>
#include <cctype>

static bool before(const Appointment& a, const Appointment& b)
{
    if (a.date != b.date)
    {
        return a.date < b.date;
    }

    return a.time < b.time;
}

void showAppointments(const HospitalData& d)
{
    if (!d.appointmentCount)
    {
        cout << "No appointments recorded.\n";
        return;
    }

    Appointment a[MAX_RECORDS];

    for (int i = 0; i < d.appointmentCount; i++)
    {
        a[i] = d.appointments[i];
    }

    for (int i = 1; i < d.appointmentCount; i++)
    {
        Appointment key = a[i];
        int j = i - 1;

        while (j >= 0 && before(key, a[j]))
        {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }

    cout << "Appointments sorted by date and time:\n";

    for (int i = 0; i < d.appointmentCount; i++)
    {
        cout << a[i].date << " " << a[i].time
             << " | Patient " << a[i].patientID
             << " | " << a[i].note << '\n';
    }
}

void addAppointment(HospitalData& d, int id, const string& user)
{
    if (findPatientIndex(d, id) < 0)
    {
        cout << "Patient not found.\n";
        return;
    }

    if (d.appointmentCount >= MAX_RECORDS)
    {
        cout << "Appointment list full.\n";
        return;
    }

    Appointment a;
    a.patientID = id;

    cout << "Date (YYYYMMDD): ";
    cin >> a.date;

    cout << "Time (HHMM): ";
    cin >> a.time;

    if (a.date.size() != 8 || a.time.size() != 4)
    {
        cout << "Use YYYYMMDD and HHMM.\n";
        return;
    }

    for (size_t i = 0; i < a.date.size(); i++)
    {
        if (!isdigit(a.date[i]))
        {
            cout << "Date must contain digits only.\n";
            return;
        }
    }

    for (size_t i = 0; i < a.time.size(); i++)
    {
        if (!isdigit(a.time[i]))
        {
            cout << "Time must contain digits only.\n";
            return;
        }
    }

    cout << "Appointment note: ";
    getline(cin >> ws, a.note);

    pushUndo(d, "Add appointment");

    d.appointments[d.appointmentCount++] = a;

    saveAll(d);

    auditAction(
        user,
        "Staff",
        "Added appointment for patient ID " + to_string(id)
    );

    cout << "Appointment saved.\n";
}

void searchAppointment(const HospitalData& d, int id)
{
    int ids[MAX_RECORDS], n = 0;

    for (int i = 0; i < d.appointmentCount; i++)
    {
        ids[n++] = i;
    }

    for (int i = 1; i < n; i++)
    {
        int key = ids[i];
        int j = i - 1;

        while (j >= 0 &&
               d.appointments[ids[j]].patientID >
               d.appointments[key].patientID)
        {
            ids[j + 1] = ids[j];
            j--;
        }

        ids[j + 1] = key;
    }

    int lo = 0, hi = n - 1, found = -1;

    while (lo <= hi)
    {
        int mid = (lo + hi) / 2;
        int pid = d.appointments[ids[mid]].patientID;

        if (pid == id)
        {
            found = mid;
            break;
        }

        if (pid < id)
        {
            lo = mid + 1;
        }
        else
        {
            hi = mid - 1;
        }
    }

    if (found < 0)
    {
        cout << "No appointment found for patient ID "
             << id << ".\n";
        return;
    }

    cout << "Appointments for patient ID " << id << ":\n";

    for (int i = 0; i < n; i++)
    {
        if (d.appointments[ids[i]].patientID == id)
        {
            cout << d.appointments[ids[i]].date
                 << " " << d.appointments[ids[i]].time
                 << " | " << d.appointments[ids[i]].note
                 << '\n';
        }
    }
}

void showReminders(const HospitalData& d)
{
    time_t now = time(NULL);
    bool any = false;

    cout << "Appointment reminders for the next 24 hours:\n";

    for (int i = 0; i < d.appointmentCount; i++)
    {
        const Appointment& a = d.appointments[i];

        if (a.date.size() != 8 || a.time.size() != 4)
        {
            continue;
        }

        tm ap = {};

        ap.tm_year = atoi(a.date.substr(0, 4).c_str()) - 1900;
        ap.tm_mon = atoi(a.date.substr(4, 2).c_str()) - 1;
        ap.tm_mday = atoi(a.date.substr(6, 2).c_str());
        ap.tm_hour = atoi(a.time.substr(0, 2).c_str());
        ap.tm_min = atoi(a.time.substr(2, 2).c_str());
        ap.tm_isdst = -1;

        time_t when = mktime(&ap);
        double seconds = difftime(when, now);

        if (seconds >= 0 && seconds <= 24 * 60 * 60)
        {
            int pi = findPatientIndex(d, a.patientID);

            cout << "Patient ID " << a.patientID
                 << (pi >= 0 ? " - " + d.patients[pi].name : "")
                 << " | " << a.date << " " << a.time
                 << " | " << a.note << '\n';

            any = true;
        }
    }

    if (!any)
    {
        cout << "No appointments scheduled within the next 24 hours.\n";
    }
}
