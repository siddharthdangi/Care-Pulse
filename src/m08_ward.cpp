#include "CarePulseModules.h"

void showBeds(const HospitalData& d)
{
    if (!d.bedCount)
    {
        cout << "No beds configured.\n";
        return;
    }

    for (int i = 0; i < d.bedCount; i++)
    {
        cout << "Bed " << d.beds[i].id
             << " | Room " << d.beds[i].roomID
             << " | " << d.beds[i].roomType
             << " | "
             << (d.beds[i].occupied
                 ? "Occupied by patient " + to_string(d.beds[i].patientID)
                 : "Available")
             << '\n';
    }
}

void addBeds(HospitalData& d, const string& user)
{
    int n;

    cout << "How many beds to add? ";
    cin >> n;

    if (n < 1 || d.bedCount + n > MAX_RECORDS)
    {
        cout << "Invalid count.\n";
        return;
    }

    pushUndo(d, "Add beds");

    for (int j = 0; j < n; j++)
    {
        Bed b;
        b.id = 1;

        for (int i = 0; i < d.bedCount; i++)
        {
            if (d.beds[i].id >= b.id)
            {
                b.id = d.beds[i].id + 1;
            }
        }

        cout << "Room ID for bed " << b.id << ": ";
        cin >> b.roomID;

        cout << "Room type (General/Semi-Private/ICU): ";
        getline(cin >> ws, b.roomType);

        b.occupied = false;
        b.patientID = 0;

        d.beds[d.bedCount++] = b;
    }

    saveAll(d);

    auditAction(user, "Staff", "Added " + to_string(n) + " beds");

    cout << "Beds added.\n";
}

void allocateBed(HospitalData& d, int id, const string& user)
{
    int pi = findPatientIndex(d, id);

    if (pi < 0)
    {
        cout << "Patient not found.\n";
        return;
    }

    Patient& p = d.patients[pi];

    if (p.admitted)
    {
        cout << "Patient already has bed " << p.bedID << ".\n";
        return;
    }

    string wanted = p.severity >= 3
        ? "ICU"
        : (p.severity == 2 ? "Semi-Private" : "General");

    int chosen = -1;

    for (int i = 0; i < d.bedCount; i++)
    {
        if (!d.beds[i].occupied && d.beds[i].roomType == wanted)
        {
            chosen = i;
            break;
        }
    }

    bool exact = true;

    if (chosen < 0)
    {
        exact = false;

        for (int i = 0; i < d.bedCount; i++)
        {
            if (!d.beds[i].occupied)
            {
                chosen = i;
                break;
            }
        }
    }

    if (chosen < 0)
    {
        cout << "No beds available.\n";
        return;
    }

    cout << "Suggested bed " << d.beds[chosen].id
         << " (" << d.beds[chosen].roomType
         << ") for severity " << severityName(p.severity) << ".\n";

    if (!exact)
    {
        cout << "Warning: no exact room-type match. "
             << "Confirm suitability with hospital staff.\n";
    }

    cout << "Confirm allocation? (1 yes, 0 no): ";
    int ok;
    cin >> ok;

    if (ok != 1)
    {
        return;
    }

    pushUndo(d, "Allocate bed");

    d.beds[chosen].occupied = true;
    d.beds[chosen].patientID = id;

    p.bedID = d.beds[chosen].id;
    p.admitted = true;
    p.status = "Admitted";

    saveAll(d);

    auditAction(
        user,
        "Staff",
        "Allocated bed " + to_string(p.bedID)
        + " to patient ID " + to_string(id)
    );

    cout << "Bed allocated.\n";
}

void releaseBed(HospitalData& d, int id, const string& user)
{
    int bi = findBedIndex(d, id);

    if (bi < 0 || !d.beds[bi].occupied)
    {
        cout << "Bed not found or already available.\n";
        return;
    }

    int pid = d.beds[bi].patientID;

    pushUndo(d, "Release bed/discharge patient");

    int pi = findPatientIndex(d, pid);

    if (pi >= 0)
    {
        d.patients[pi].admitted = false;
        d.patients[pi].bedID = 0;
        d.patients[pi].status = "Discharged";
    }

    d.beds[bi].occupied = false;
    d.beds[bi].patientID = 0;

    saveAll(d);

    auditAction(
        user,
        "Staff",
        "Released bed " + to_string(id)
        + " and discharged patient ID " + to_string(pid)
    );

    cout << "Bed released; patient status is Discharged.\n";
}
