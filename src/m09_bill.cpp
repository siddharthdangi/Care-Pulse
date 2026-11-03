#include "CarePulseModules.h"
#include <iomanip>

void createBill(HospitalData& d, int id, const string& user)
{
    if (findPatientIndex(d, id) < 0)
    {
        cout << "Patient not found.\n";
        return;
    }

    if (d.billCount >= MAX_RECORDS)
    {
        cout << "Bill list is full.\n";
        return;
    }

    Bill b;
    b.patientID = id;

    cout << "Bill description: ";
    getline(cin >> ws, b.description);

    cout << "Subtotal amount: ";
    cin >> b.subtotal;

    if (b.subtotal < 0)
    {
        cout << "Amount cannot be negative.\n";
        return;
    }

    b.tax = b.subtotal * 0.05;
    b.total = b.subtotal + b.tax;

    pushUndo(d, "Create bill");

    d.bills[d.billCount++] = b;

    saveAll(d);

    auditAction(
        user,
        "Staff",
        "Created bill for patient ID " + to_string(id)
    );

    cout << fixed << setprecision(2)
         << "Subtotal: " << b.subtotal
         << "\nProject tax (5%): " << b.tax
         << "\nTotal: " << b.total << "\n";
}

void showBills(const HospitalData& d)
{
    if (!d.billCount)
    {
        cout << "No bills recorded.\n";
        return;
    }

    for (int i = 0; i < d.billCount; i++)
    {
        cout << fixed << setprecision(2)
             << "Patient ID " << d.bills[i].patientID
             << " | " << d.bills[i].description
             << " | Total: " << d.bills[i].total
             << '\n';
    }
}
