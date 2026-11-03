#include "CarePulseModules.h"
#include <fstream>
#include <cstdlib>

static string currentUser, currentRole;

static bool authenticate(HospitalData& d)
{
    if (d.userCount == 0)
    {
        cout << "First run: create the first STAFF account.\n";

        User u;
        string p, c;

        cout << "Staff username: ";
        cin >> u.username;

        do
        {
            cout << "Password (8+ characters, uppercase, lowercase and number): ";
            cin >> p;

            if (!validPassword(p))
            {
                cout << "Password does not meet the rules. Try again.\n";
                continue;
            }

            cout << "Confirm password: ";
            cin >> c;

            if (p != c)
            {
                cout << "Passwords do not match.\n";
                continue;
            }

            break;

        } while (true);

        u.role = "Staff";
        u.salt = makeSalt();
        u.passwordHash = passwordDigest(u.salt, p);

        d.users[d.userCount++] = u;

        currentUser = u.username;
        currentRole = u.role;

        saveAll(d);
        auditAction(currentUser, currentRole, "Created initial staff account");

        return true;
    }

    for (int tries = 0; tries < 5; tries++)
    {
        string name, pw;

        cout << "Username: ";
        cin >> name;

        cout << "Password: ";
        cin >> pw;

        for (int i = 0; i < d.userCount; i++)
        {
            if (d.users[i].username == name &&
                d.users[i].passwordHash == passwordDigest(d.users[i].salt, pw))
            {
                if (d.users[i].role != "Staff" &&
                    d.users[i].role != "Doctor")
                {
                    cout << "This role cannot log in.\n";
                    return false;
                }

                currentUser = name;
                currentRole = d.users[i].role;

                auditAction(currentUser, currentRole, "Logged in");

                return true;
            }
        }

        cout << "Invalid username or password. Attempts left: "
             << 4 - tries << '\n';
    }

    cout << "Too many failed attempts. Restart the program to try again.\n";

    return false;
}

static void createAccount(HospitalData& d)
{
    if (currentRole != "Staff")
    {
        cout << "Only staff can create accounts.\n";
        return;
    }

    if (d.userCount >= MAX_RECORDS)
    {
        cout << "Account limit reached.\n";
        return;
    }

    User u;
    string p, c;

    cout << "New username: ";
    cin >> u.username;

    for (int i = 0; i < d.userCount; i++)
    {
        if (d.users[i].username == u.username)
        {
            cout << "Username already exists.\n";
            return;
        }
    }

    cout << "New password (8+ characters, uppercase, lowercase and number): ";
    cin >> p;

    if (!validPassword(p))
    {
        cout << "Password does not meet the rules.\n";
        return;
    }

    cout << "Confirm password: ";
    cin >> c;

    if (p != c)
    {
        cout << "Passwords do not match.\n";
        return;
    }

    int r;

    cout << "Role: 1 Staff, 2 Doctor (patients cannot log in): ";
    cin >> r;

    if (r != 1 && r != 2)
    {
        cout << "Invalid role.\n";
        return;
    }

    pushUndo(d, "Create user account");

    u.role = r == 1 ? "Staff" : "Doctor";
    u.salt = makeSalt();
    u.passwordHash = passwordDigest(u.salt, p);

    d.users[d.userCount++] = u;

    saveAll(d);

    auditAction(currentUser, currentRole,
               "Created " + u.role + " account: " + u.username);

    cout << "Account created.\n";
}

static void showDoctors(const HospitalData& d)
{
    if (!d.doctorCount)
    {
        cout << "No doctors registered.\n";
        return;
    }

    for (int i = 0; i < d.doctorCount; i++)
    {
        cout << "ID " << d.doctors[i].id << " | "
             << d.doctors[i].name << " | "
             << d.doctors[i].specialization << '\n';
    }
}

void showDailySummary(const HospitalData& d)
{
    int waiting = 0, emerg = 0, admitted = 0;
    double revenue = 0;

    for (int i = 0; i < d.patientCount; i++)
    {
        if (d.patients[i].status == "Waiting for OPD")
            waiting++;

        if (d.patients[i].status == "Waiting for emergency")
            emerg++;

        if (d.patients[i].admitted)
            admitted++;
    }

    for (int i = 0; i < d.billCount; i++)
        revenue += d.bills[i].total;

    time_t now = time(NULL);
    tm *t = localtime(&now);
    char today[11];

    strftime(today, sizeof(today), "%Y-%m-%d", t);

    int todayActions = 0;

    ifstream log("audit.log");
    string line;

    while (getline(log, line))
    {
        if (line.size() >= 10 && line.substr(0, 10) == today)
            todayActions++;
    }

    log.close();

    cout << "\n===== DAILY SUMMARY =====\n";
    cout << "Date: " << today << "\n";
    cout << "Actions recorded today: " << todayActions << "\n";
    cout << "Current patient records: " << d.patientCount << "\n";
    cout << "Doctors: " << d.doctorCount << "\n";
    cout << "OPD waiting: " << waiting << "\n";
    cout << "Emergency waiting: " << emerg << "\n";
    cout << "Beds occupied: " << admitted << " / " << d.bedCount << "\n";
    cout << "Appointments stored: " << d.appointmentCount << "\n";
    cout << "Bills stored: " << d.billCount << "\n";
    cout << "Recorded billed total: " << revenue << "\n";
}

void showAlerts(const HospitalData& d)
{
    bool any = false;
    int incomplete = 0, unassigned = 0;

    for (int i = 0; i < d.patientCount; i++)
    {
        if (d.patients[i].name.empty() ||
            d.patients[i].diagnosis.empty())
            incomplete++;

        if (d.patients[i].doctorID == 0 &&
            d.patients[i].status != "Discharged")
            unassigned++;
    }

    cout << "\n===== CARE-PULSE ALERTS =====\n";

    if (opdCount() > 5)
    {
        cout << "Alert: OPD queue is long ("
             << opdCount() << " waiting).\n";
        any = true;
    }

    if (incomplete)
    {
        cout << "Alert: " << incomplete
             << " patient record(s) have incomplete name/diagnosis.\n";
        any = true;
    }

    if (unassigned)
    {
        cout << "Alert: " << unassigned
             << " patient(s) have no doctor assigned.\n";
        any = true;
    }

    int free = 0;

    for (int i = 0; i < d.bedCount; i++)
    {
        if (!d.beds[i].occupied)
            free++;
    }

    if (d.patientCount && d.bedCount && free == 0)
    {
        cout << "Alert: no beds currently available.\n";
        any = true;
    }

    showReminders(d);

    if (!any)
        cout << "No queue, record, assignment, or bed alerts at this time.\n";
}

void showJourney(const HospitalData& d, int id)
{
    int i = findPatientIndex(d, id);

    if (i < 0)
    {
        cout << "Patient not found.\n";
        return;
    }

    const Patient& p = d.patients[i];

    cout << "Patient journey: " << p.name
         << " (ID " << id << ")\n";

    cout << "Registered -> ";

    if (p.status == "Waiting for OPD")
        cout << "Waiting for OPD";
    else if (p.status == "In consultation")
        cout << "In consultation";
    else if (p.status == "Waiting for emergency")
        cout << "Waiting for emergency";
    else if (p.status == "Emergency case attended")
        cout << "Emergency case attended";
    else
        cout << p.status;

    if (p.admitted)
        cout << " -> Admitted (bed " << p.bedID << ")";

    cout << '\n';
}

static void doctorMenu(HospitalData& d)
{
    int c;

    do
    {
        cout << "\n===== DOCTOR MENU (VIEW ONLY) =====\n";
        cout << "1. View all patients\n";
        cout << "2. View patient by ID\n";
        cout << "3. View OPD queue\n";
        cout << "4. View emergency queue\n";
        cout << "5. View appointments\n";
        cout << "0. Logout\n";
        cout << "Choice: ";

        cin >> c;

        if (c == 1)
            showAllPatients(d);
        else if (c == 2)
        {
            int id;

            cout << "Patient ID: ";
            cin >> id;

            showPatient(d, id);
        }
        else if (c == 3)
            opdDisplay(d);
        else if (c == 4)
            emergencyDisplay(d);
        else if (c == 5)
            showAppointments(d);
        else if (c != 0)
            cout << "Invalid choice.\n";

    } while (c != 0);
}

static void staffMenu(HospitalData& d)
{
    int c;

    do
    {
        cout << "\n===== CARE-PULSE STAFF MENU =====\n";
        cout << "1 Register patient\n";
        cout << "2 Add doctor\n";
        cout << "3 View all patients\n";
        cout << "4 Search patient (BST)\n";
        cout << "5 Edit patient details\n";
        cout << "6 Add patient to OPD\n";
        cout << "7 Serve next OPD patient\n";
        cout << "8 Add emergency case\n";
        cout << "9 Serve next emergency case\n";
        cout << "10 Add beds\n";
        cout << "11 View beds\n";
        cout << "12 Suggest/allocate bed\n";
        cout << "13 Release bed / discharge\n";
        cout << "14 Create bill\n";
        cout << "15 View bills\n";
        cout << "16 Add appointment\n";
        cout << "17 View sorted appointments\n";
        cout << "18 Search appointment by patient ID (Binary Search)\n";
        cout << "19 Appointment reminders\n";
        cout << "20 Daily summary\n";
        cout << "21 Alerts\n";
        cout << "22 Patient journey/status\n";
        cout << "23 Create staff/doctor account\n";
        cout << "24 Undo last operation\n";
        cout << "25 Recent undo history\n";
        cout << "26 Change average OPD consultation minutes\n";
        cout << "27 View doctor list\n";
        cout << "0 Logout\n";
        cout << "Choice: ";

        cin >> c;

        int id;
        string action;

        switch (c)
        {
            case 1:
                registerPatient(d, currentUser);
                break;

            case 2:
                addDoctor(d, currentUser);
                break;

            case 3:
                showAllPatients(d);
                break;

            case 4:
                cout << "Patient ID: ";
                cin >> id;

                if (bstContains(id))
                    showPatient(d, id);
                else
                    cout << "Patient not found in BST.\n";

                break;

            case 5:
                editPatient(d, currentUser);
                break;

            case 6:
                cout << "Patient ID: ";
                cin >> id;

                addToOPD(d, id, currentUser);
                break;

            case 7:
                serveOPD(d, currentUser);
                break;

            case 8:
                cout << "Patient ID: ";
                cin >> id;

                addEmergencyCase(d, id, currentUser);
                break;

            case 9:
                serveEmergencyCase(d, currentUser);
                break;

            case 10:
                addBeds(d, currentUser);
                break;

            case 11:
                showBeds(d);
                break;

            case 12:
                cout << "Patient ID to admit: ";
                cin >> id;

                allocateBed(d, id, currentUser);
                break;

            case 13:
                cout << "Bed ID to release: ";
                cin >> id;

                releaseBed(d, id, currentUser);
                break;

            case 14:
                cout << "Patient ID: ";
                cin >> id;

                createBill(d, id, currentUser);
                break;

            case 15:
                showBills(d);
                break;

            case 16:
                cout << "Patient ID: ";
                cin >> id;

                addAppointment(d, id, currentUser);
                break;

            case 17:
                showAppointments(d);
                break;

            case 18:
                cout << "Patient ID: ";
                cin >> id;

                searchAppointment(d, id);
                break;

            case 19:
                showReminders(d);
                break;

            case 20:
                showDailySummary(d);
                break;

            case 21:
                showAlerts(d);
                break;

            case 22:
                cout << "Patient ID: ";
                cin >> id;

                showJourney(d, id);
                break;

            case 23:
                createAccount(d);
                break;

            case 24:
                if (undoLast(d, action))
                {
                    rebuildStructures(d);
                    saveAll(d);

                    auditAction(currentUser, currentRole,
                               "Undo operation: " + action);

                    cout << "Undid: " << action
                         << ". Shared records and indexes restored.\n";
                }
                else
                {
                    cout << "Nothing to undo.\n";
                }

                break;

            case 25:
                showUndoHistory();
                break;

            case 26:
                cout << "Average consultation minutes (1-240): ";
                cin >> id;

                if (id < 1 || id > 240)
                {
                    cout << "Invalid value.\n";
                }
                else
                {
                    pushUndo(d, "Change average consultation time");

                    d.averageConsultMinutes = id;

                    saveAll(d);

                    auditAction(currentUser, currentRole,
                               "Changed average consultation time");

                    cout << "Waiting-time estimate updated.\n";
                }

                break;

            case 27:
                showDoctors(d);
                break;

            case 0:
                auditAction(currentUser, currentRole, "Logged out");
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (c != 0);
}

int main()
{
    HospitalData data;

    loadAll(data);

    if (!authenticate(data))
        return 0;

    cout << "\nLogin successful. Role: " << currentRole << "\n";

    if (currentRole == "Staff")
        staffMenu(data);
    else
        doctorMenu(data);

    cout << "Care-Pulse closed. Data saved in text files; "
         << "do not use real patient information in this educational prototype.\n";

    return 0;
}
