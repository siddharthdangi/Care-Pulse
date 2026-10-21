#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
int main() {
    int id, n;
    double amount, total = 0;
    cout << "Enter patient ID: ";
    cin >> id;
    cout << "Enter number of bill items: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        string name;
        cout << "\nEnter item name: ";
        cin >> ws;
        getline(cin, name);
        cout << "Enter amount: ";
        cin >> amount;
        if (amount < 0)
            amount = 0;
        total += amount;
    }
    double tax = total * 0.05;
    cout << fixed << setprecision(2);
    cout << "\n--- HOSPITAL BILL ---\n";
    cout << "Patient ID: " << id << endl;
    cout << "Subtotal: Rs " << total << endl;
    cout << "Tax (5%): Rs " << tax << endl;
    cout << "Total: Rs " << total + tax << endl;
    return 0;
}
