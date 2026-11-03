#ifndef CAREPULSE_MODULES_H
#define CAREPULSE_MODULES_H

#include <iostream>
#include <string>

using namespace std;

const int MAX_RECORDS = 200;
const int MAX_UNDO = 20;

struct Person
{
    int id, age;
    string name;

    Person();

    virtual string role() const = 0;
    virtual ~Person();
};

struct Patient : Person
{
    string diagnosis, status;
    int severity, doctorID, bedID, queueOrder, emergencyOrder;
    bool admitted;

    Patient() : severity(1), doctorID(0), bedID(0),
               queueOrder(0), emergencyOrder(0), admitted(false)
    {
    }

    string role() const override;
};

struct Doctor : Person
{
    string specialization;

    Doctor()
    {
    }

    string role() const override;
};

struct Staff : Person
{
    string jobRole;

    Staff()
    {
    }

    string role() const override;
};

struct Bed
{
    int id, roomID, patientID;
    string roomType;
    bool occupied;

    Bed() : id(0), roomID(0), patientID(0), occupied(false)
    {
    }
};

struct Appointment
{
    int patientID;
    string date, time, note;

    Appointment() : patientID(0)
    {
    }
};

struct Bill
{
    int patientID;
    double subtotal, tax, total;
    string description;

    Bill() : patientID(0), subtotal(0), tax(0), total(0)
    {
    }
};

struct User
{
    string username, salt, passwordHash, role;
};

struct HospitalData
{
    Patient patients[MAX_RECORDS];
    int patientCount;

    Doctor doctors[MAX_RECORDS];
    int doctorCount;

    Bed beds[MAX_RECORDS];
    int bedCount;

    Appointment appointments[MAX_RECORDS];
    int appointmentCount;

    Bill bills[MAX_RECORDS];
    int billCount;

    User users[MAX_RECORDS];
    int userCount;

    int nextArrival, averageConsultMinutes;

    HospitalData() : patientCount(0), doctorCount(0), bedCount(0),
                     appointmentCount(0), billCount(0), userCount(0),
                     nextArrival(1), averageConsultMinutes(15)
    {
    }
};

string severityName(int severity);

string makeSalt();

string passwordDigest(const string& salt, const string& password);

bool validPassword(const string& password);

int findPatientIndex(const HospitalData& d, int id);

int findDoctorIndex(const HospitalData& d, int id);

int findBedIndex(const HospitalData& d, int id);

void auditAction(const string& username, const string& role,
                 const string& action);

void saveAll(const HospitalData& d);

void loadAll(HospitalData& d);

void rebuildStructures(const HospitalData& d);

void linkedListAdd(const Patient& p);
void linkedListRebuild(const HospitalData& d);
void linkedListDisplay();

void opdRebuild(const HospitalData& d);
bool opdContains(int id);
int opdCount();
void opdAdd(int id);
int opdServe();
void opdRemove(int id);
void opdDisplay(const HospitalData& d);

void emergencyRebuild(const HospitalData& d);
bool emergencyContains(int id);
int emergencyCount();
void emergencyAdd(const HospitalData& d, int id);
int emergencyServe();
void emergencyRemove(int id);
void emergencyDisplay(const HospitalData& d);

void bstRebuild(const HospitalData& d);
bool bstContains(int id);

void hashRebuild(const HospitalData& d);
int hashDoctorIndex(int id);

void pushUndo(const HospitalData& d, const string& action);
bool undoLast(HospitalData& d, string& action);
void clearUndo();
void showUndoHistory();

void showBeds(const HospitalData& d);
void addBeds(HospitalData& d, const string& username);
void allocateBed(HospitalData& d, int patientID, const string& username);
void releaseBed(HospitalData& d, int bedID, const string& username);

void createBill(HospitalData& d, int patientID, const string& username);
void showBills(const HospitalData& d);

void addAppointment(HospitalData& d, int patientID, const string& username);
void showAppointments(const HospitalData& d);
void searchAppointment(const HospitalData& d, int patientID);
void showReminders(const HospitalData& d);

void registerPatient(HospitalData& d, const string& username);
void addDoctor(HospitalData& d, const string& username);
void editPatient(HospitalData& d, const string& username);
void showPatient(const HospitalData& d, int id);
void showAllPatients(const HospitalData& d);

void showDailySummary(const HospitalData& d);
void showAlerts(const HospitalData& d);
void showJourney(const HospitalData& d, int id);

void addToOPD(HospitalData& d, int id, const string& username);
void serveOPD(HospitalData& d, const string& username);

void addEmergencyCase(HospitalData& d, int id, const string& username);
void serveEmergencyCase(HospitalData& d, const string& username);

#endif
