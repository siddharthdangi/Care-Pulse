#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Patient {
    int id, age;
    string name;
};
struct Doctor {
    int id;
    string name, specialization;
};
int main() {
    Patient p;
    Doctor d;
    int n, m;
    ofstream pf("patients.txt");
    ofstream df("doctors.txt");
    cout << "Enter number of patients: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Patient ID: ";
        cin >> p.id;
        cout << "Patient name: ";
        getline(cin >> ws, p.name);
        cout << "Patient age: ";
        cin >> p.age;
        pf << p.id << "|" << p.name << "|" << p.age << endl;
    }
    cout << "Enter number of doctors: ";
    cin >> m;
    for (int i = 0; i < m; i++) {
        cout << "Doctor ID: ";
        cin >> d.id;
        cout << "Doctor name: ";
        getline(cin >> ws, d.name);
        cout << "Specialization: ";
        getline(cin >> ws, d.specialization);
        df << d.id << "|" << d.name << "|"
           << d.specialization << endl;
    }
    pf.close();
    df.close();
    string line;
    cout << "\nPatient Records:\n";
    ifstream pr("patients.txt");
    while (getline(pr, line))
        cout << line << endl;
    pr.close();
    cout << "\nDoctor Records:\n";
    ifstream dr("doctors.txt");
    while (getline(dr, line))
        cout << line << endl;
    dr.close();
    return 0;
}
