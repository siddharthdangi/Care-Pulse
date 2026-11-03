#include "CarePulseModules.h"

class PatientLinkedList
{
    struct Node
    {
        Patient data;
        Node* next;

        Node(const Patient& p) : data(p), next(NULL)
        {
        }
    };

    Node* head;

public:
    PatientLinkedList() : head(NULL)
    {
    }

    ~PatientLinkedList()
    {
        clear();
    }

    void clear()
    {
        while (head)
        {
            Node* t = head;
            head = head->next;
            delete t;
        }
    }

    void add(const Patient& p)
    {
        Node* n = new Node(p);

        if (!head)
        {
            head = n;
        }
        else
        {
            Node* c = head;

            while (c->next)
            {
                c = c->next;
            }

            c->next = n;
        }
    }

    void display()
    {
        if (!head)
        {
            cout << "No patient records found.\n";
            return;
        }

        Node* c = head;

        while (c)
        {
            cout << "ID " << c->data.id << " | "
                 << c->data.name << " | Age "
                 << c->data.age << " | "
                 << c->data.diagnosis << " | "
                 << c->data.status << '\n';

            c = c->next;
        }
    }
};

static PatientLinkedList patientList;

void linkedListRebuild(const HospitalData& d)
{
    patientList.clear();

    for (int i = 0; i < d.patientCount; i++)
    {
        patientList.add(d.patients[i]);
    }
}

void linkedListAdd(const Patient& p)
{
    patientList.add(p);
}

void linkedListDisplay()
{
    patientList.display();
}

int findPatientIndex(const HospitalData& d, int id)
{
    for (int i = 0; i < d.patientCount; i++)
    {
        if (d.patients[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

int findDoctorIndex(const HospitalData& d, int id)
{
    for (int i = 0; i < d.doctorCount; i++)
    {
        if (d.doctors[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

int findBedIndex(const HospitalData& d, int id)
{
    for (int i = 0; i < d.bedCount; i++)
    {
        if (d.beds[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

void registerPatient(HospitalData& d, const string& user)
{
    if (d.patientCount >= MAX_RECORDS)
    {
        cout << "Patient list is full.\n";
        return;
    }

    Patient p;

    cout << "Patient ID: ";
    cin >> p.id;

    if (p.id <= 0 || findPatientIndex(d, p.id) >= 0)
    {
        cout << "Invalid or duplicate ID.\n";
        return;
    }

    cout << "Patient name: ";
    getline(cin >> ws, p.name);

    cout << "Age: ";
    cin >> p.age;

    if (p.age < 0 || p.age > 120)
    {
        cout << "Invalid age.\n";
        return;
    }

    cout << "Diagnosis/reason: ";
    getline(cin >> ws, p.diagnosis);

    cout << "Severity (1 Stable, 2 Moderate, 3 Severe, 4 Critical): ";
    cin >> p.severity;

    if (p.severity < 1 || p.severity > 4)
    {
        cout << "Invalid severity.\n";
        return;
    }

    cout << "Doctor ID (0 if not assigned): ";
    cin >> p.doctorID;

    if (p.doctorID != 0 && findDoctorIndex(d, p.doctorID) < 0)
    {
        cout << "Doctor not found; leaving unassigned.\n";
        p.doctorID = 0;
    }

    p.status = "Registered";
    p.queueOrder = 0;
    p.emergencyOrder = 0;
    p.admitted = false;
    p.bedID = 0;

    pushUndo(d, "Register patient");

    d.patients[d.patientCount++] = p;

    linkedListRebuild(d);
    bstRebuild(d);
    saveAll(d);

    auditAction(user, "Staff", "Registered patient ID " + to_string(p.id));

    cout << "Patient registered.\n";
}

void editPatient(HospitalData& d, const string& user)
{
    int id;

    cout << "Patient ID to edit: ";
    cin >> id;

    int i = findPatientIndex(d, id);

    if (i < 0)
    {
        cout << "Patient not found.\n";
        return;
    }

    Patient old = d.patients[i];
    Patient p = old;

    cout << "New name (0 to keep current): ";
    string s;
    getline(cin >> ws, s);

    if (s != "0" && !s.empty())
    {
        p.name = s;
    }

    cout << "New age (0 to keep current): ";
    int a;
    cin >> a;

    if (a != 0)
    {
        if (a < 1 || a > 120)
        {
            cout << "Invalid age.\n";
            return;
        }

        p.age = a;
    }

    cout << "New diagnosis (0 to keep current): ";
    getline(cin >> ws, s);

    if (s != "0" && !s.empty())
    {
        p.diagnosis = s;
    }

    cout << "New severity 1-4 (0 to keep): ";
    int sev;
    cin >> sev;

    if (sev != 0)
    {
        if (sev < 1 || sev > 4)
        {
            cout << "Invalid severity.\n";
            return;
        }

        p.severity = sev;
    }

    cout << "Doctor ID (0 keep current, -1 unassign): ";
    int did;
    cin >> did;

    if (did == -1)
    {
        p.doctorID = 0;
    }
    else if (did > 0)
    {
        if (findDoctorIndex(d, did) < 0)
        {
            cout << "Doctor not found.\n";
            return;
        }

        p.doctorID = did;
    }

    pushUndo(d, "Edit patient ID " + to_string(id));

    d.patients[i] = p;

    linkedListRebuild(d);
    bstRebuild(d);
    saveAll(d);

    auditAction(
        user,
        "Staff",
        "Edited patient ID " + to_string(id)
        + ": name [" + old.name + " -> " + p.name
        + "], age [" + to_string(old.age) + " -> " + to_string(p.age)
        + "], diagnosis [" + old.diagnosis + " -> " + p.diagnosis
        + "], severity [" + severityName(old.severity) + " -> "
        + severityName(p.severity)
        + "], doctor ID [" + to_string(old.doctorID) + " -> "
        + to_string(p.doctorID) + "]"
    );

    cout << "Patient updated.\n";
}

void showPatient(const HospitalData& d, int id)
{
    int i = findPatientIndex(d, id);

    if (i < 0)
    {
        cout << "Patient not found.\n";
        return;
    }

    const Patient& p = d.patients[i];

    cout << "ID: " << p.id
         << "\nName: " << p.name
         << "\nAge: " << p.age
         << "\nDiagnosis: " << p.diagnosis
         << "\nSeverity: " << severityName(p.severity)
         << "\nDoctor ID: " << p.doctorID
         << "\nStatus: " << p.status
         << "\nBed ID: " << p.bedID << "\n";
}

void showAllPatients(const HospitalData& d)
{
    if (!d.patientCount)
    {
        cout << "No patients registered.\n";
        return;
    }

    for (int i = 0; i < d.patientCount; i++)
    {
        showPatient(d, d.patients[i].id);
    }
}
