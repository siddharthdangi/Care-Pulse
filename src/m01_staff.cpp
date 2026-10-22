#include <iostream>
#include <string>
using namespace std;
class Staff
{
    int id, age;
    string name, jobRole;
public:
    void input()
    {
        cout << "Enter staff ID: ";
        cin >> id;
        cout << "Enter name: ";
        getline(cin >> ws, name);
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter staff role: ";
        getline(cin >> ws, jobRole);
        cout<<"\n ************************ \n";
    }
    void display()
    {
        cout << "\n--- Staff Record ---\n";
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Staff Role: " << jobRole << endl;
    }
};
int main()
{
    int n,i=0;
    cout<<"Enter number of staff members\n";
    cin>> n;
    Staff s[n];
    while(i!=n)
    {
        s[i].input();
            i++;
    } 
    i=0;
    while(i!=n)
    {
        s[i].display();
            i++;
     }
    return 0;
}
