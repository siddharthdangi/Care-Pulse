#include <iostream>
#include <string>
using namespace std;
class Doctor
{
    int id, age;
    string name, specialization;
public:
    void input()
    {
        cout << "Enter doctor ID: ";
        cin >> id;
        cout << "Enter name: ";
        getline(cin >> ws, name);
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter specialization: ";
        getline(cin >> ws, specialization);
    }
    void display()
    {
        cout << "\n--- Doctor Record ---\n";
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Specialization: " << specialization << endl;
    }
    string role()
    {
        return "Doctor";
    }
};
int main()
{
    int n,i=0;
    cout<<"Enter number of doctors\n";
    cin>> n;
    Doctor d[n];
    while(i!=n)
    {
        d[i].input();
            i++;
     }
    i=0;
    while(i!=n)
    {
        d[i].display();
            i++;
     }
    return 0;
}
