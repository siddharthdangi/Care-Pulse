#include <iostream>
#include <string>
using namespace std;
struct User
{
    string username;
    string password;
    string role;
};
int main()
{
    User users[3] = {{"staff1", "staff123", "Staff"}, {"doctor1", "doc123", "Doctor"}, {"patient1", "pat123", "Patient"} };
    string username, password;
    int choice;
    while (true)
    {
        cout << "\n===== CARE-PULSE LOGIN =====\n";
        cout << "1. Login\n";
        cout << "2. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 2)
        {
            cout << "Exiting Care-Pulse...\n";
            break;
        }
        if (choice != 1)
        {
            cout << "Invalid choice!\n";
            continue;
        }
        cout << "\nEnter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        bool loggedIn = false;
        string role = "";        
        for (int i = 0; i < 3; i++)
        {
            if (users[i].username == username &&
                users[i].password == password)
            {
                loggedIn = true;
                role = users[i].role;
                break;
            }
        }
        if (!loggedIn)
        {
            cout << "\nInvalid username or password!\n";
            continue;
        }
        if (role == "Patient")
        {
            cout << "\nAccess denied! Only staff and doctors can log in.\n";
            continue;
        }
        cout << "\nLogin successful!\n";
        cout << "Welcome, " << role << "!\n";
        if (role == "Staff")
        {
            int option;
            do
            {
                cout << "\n===== STAFF DASHBOARD =====\n";
                cout << "1. Register Patient\n";
                cout << "2. View Patient Details\n";
                cout << "3. Manage Appointments\n";
                cout << "4. Manage Admissions\n";
                cout << "5. Manage Billing\n";
                cout << "6. Logout\n";
                cout << "Enter choice: ";
                cin >> option;
                switch (option)
                {
                    case 1:
                        cout << "Patient registration selected.\n";
                        break;

                    case 2:
                        cout << "View patient details selected.\n";
                        break;

                    case 3:
                        cout << "Appointment management selected.\n";
                        break;

                    case 4:
                        cout << "Admission management selected.\n";
                        break;

                    case 5:
                        cout << "Billing management selected.\n";
                        break;

                    case 6:
                        cout << "Staff logged out successfully.\n";
                        break;

                    default:
                        cout << "Invalid choice!\n";
                }
            } while (option != 6);
        }
        else if (role == "Doctor")
        {
            int option;
            do
            {
                cout << "\n===== DOCTOR DASHBOARD =====\n";
                cout << "1. View Patient Details\n";
                cout << "2. Logout\n";
                cout << "Enter choice: ";
                cin >> option;
                switch (option)
                {
                    case 1:
                        cout << "View patient details selected.\n";
                        break;

                    case 2:
                        cout << "Doctor logged out successfully.\n";
                        break;

                    default:
                        cout << "Invalid choice!\n";
                }
            } while (option != 2);
        }
    }
    return 0;
}
