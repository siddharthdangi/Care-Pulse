#include <iostream>
#include <string>
using namespace std;
struct Patient
{
    int id;
    string name;
    int severity;
    int arrivalOrder;
};
int main()
{
    Patient patients[100];
    int n;
    cout << "How many emergency patients? ";
    cin >> n;
    if (n < 1 || n > 100)
    {
        cout << "Please enter a number between 1 and 100.\n";
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        cout << "\nPatient ID: ";
        cin >> patients[i].id;
        cout << "Patient name: ";
        getline(cin >> ws, patients[i].name);
        cout << "Severity (1 Stable, 2 Moderate, 3 Severe, 4 Critical): ";
        cin >> patients[i].severity;
        if (patients[i].severity < 1 || patients[i].severity > 4)
        {
            cout << "Invalid severity. Enter again: ";
            cin >> patients[i].severity;
            while (patients[i].severity < 1 || patients[i].severity > 4)
            {
                cout << "Enter severity between 1 and 4: ";
                cin >> patients[i].severity;
            }
        }
        patients[i].arrivalOrder = i;
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (patients[i].severity < patients[j].severity || (patients[i].severity == patients[j].severity && patients[i].arrivalOrder > patients[j].arrivalOrder))
            {
                Patient temp = patients[i];
                patients[i] = patients[j];
                patients[j] = temp;
            }
        }
    }
    cout << "\n===== EMERGENCY PATIENT QUEUE =====\n";
    for (int i = 0; i < n; i++)
    {
        cout << "\nPatient ID: " << patients[i].id;
        cout << "\nName: " << patients[i].name;
        cout << "\nSeverity: " << patients[i].severity;
        if (patients[i].severity == 1)
            cout << " (Stable)";
        else if (patients[i].severity == 2)
            cout << " (Moderate)";
        else if (patients[i].severity == 3)
            cout << " (Severe)";
        else
            cout << " (Critical)";
        cout << "\n";
    }
    cout << "\nServe the highest-priority patient? (1 Yes, 0 No): ";
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        cout << "\nServing patient: " << patients[0].name;
        cout << " (ID " << patients[0].id << ")\n";
        for (int i = 0; i < n - 1; i++)
        {
            patients[i] = patients[i + 1];
        }
        n--;
        cout << "\n===== REMAINING PATIENTS =====\n";
        for (int i = 0; i < n; i++)
        {
            cout << patients[i].name
                 << " (ID " << patients[i].id << ")"
                 << " - Severity " << patients[i].severity << "\n";
        }
        if (n == 0)
            cout << "No patients waiting.\n";
    }
    return 0;
}
