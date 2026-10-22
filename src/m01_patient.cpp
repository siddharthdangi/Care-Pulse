#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
class Patient
{
    int id, age, doctorID, bedID;
    string name, diagnosis, severity;
    bool admitted;
public:
    void input()
    {
        cout << "Enter patient ID: ";
        cin >> id;
        cout << "Enter name: ";
        getline(cin >> ws, name);
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter diagnosis: ";
        getline(cin >> ws, diagnosis);
        int choice;
        do
        {
            cout << "\nSelect severity:\n";
            cout << "1. Stable\n";
            cout << "2. Moderate\n";
            cout << "3. Severe\n";
            cout << "4. Critical\n";
            cout << "Enter your choice (1-4): ";
            cin >> choice;
            if (choice < 1 || choice > 4)
            {
                cout << "Invalid choice! Please enter a number from 1 to 4.\n";
            }
        } while (choice < 1 || choice > 4);
        if (choice == 1)
            severity = "Stable";
        else if (choice == 2)
            severity = "Moderate";
        else if (choice == 3)
            severity = "Severe";
        else
            severity = "Critical";
        cout << "Enter doctor ID: ";
        cin >> doctorID;
        int answer;
        cout << "Is patient admitted? (1 Yes, 0 No): ";
        cin >> answer;
        admitted = (answer == 1);
        if (admitted)
        {
            cout << "Enter bed ID: ";
            cin >> bedID;
        }
        else
        {
            bedID = 0;
        }
    }
    void display()
    {
        cout << left
             << setw(8) << id
             << setw(18) << name
             << setw(8) << age
             << setw(20) << diagnosis
             << setw(12) << severity
             << setw(12) << doctorID;
        if (admitted)
            cout << setw(8) << bedID;
        else
            cout << setw(8) << "N/A";
        cout << endl;
    }
};

int main()
{
    Patient p[100];
    int n;
    cout << "Enter number of patients (1-100): ";
    cin >> n;
    if (n < 1 || n > 100)
    {
        cout << "Invalid number of patients!" << endl;
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter details for Patient " << i + 1 << endl;
        cout << "-----------------------------\n";
        p[i].input();
    }
    cout << "\n==================== CARE-PULSE PATIENT RECORDS ====================\n\n";
    cout << left
         << setw(8) << "ID"
         << setw(18) << "Name"
         << setw(8) << "Age"
         << setw(20) << "Diagnosis"
         << setw(12) << "Severity"
         << setw(12) << "Doctor ID"
         << setw(8) << "Bed ID" << endl;
    cout << string(86, '-') << endl;
    for (int i = 0; i < n; i++)
    {
        p[i].display();
    }
    return 0;
}
