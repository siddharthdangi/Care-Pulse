// MODULE 2: Linked List of patient records
#include <iostream>
#include <string>
using namespace std;
struct Patient { int id; string name; };
struct Node { Patient data; Node* next; Node(Patient p) : data(p), next(nullptr) {} };
class LinkedList {
    Node* head;
public:
    LinkedList() : head(nullptr) {}
    void add(Patient p) {
        Node* n = new Node(p);
        if (head == nullptr) head = n;
        else { Node* cur = head; while (cur->next != nullptr) cur = cur->next; cur->next = n; }
    }
    void display() const {
        Node* cur = head;
        if (!cur) cout << "No patients recorded.\n";
        while (cur) { cout << "ID: " << cur->data.id << ", Name: " << cur->data.name << '\n'; cur = cur->next; }
    }
    ~LinkedList() { while (head) { Node* old = head; head = head->next; delete old; } }
};
int main() {
    LinkedList patients;
    int n;
    cout << "How many patients do you want to enter? "; cin >> n;
    for (int i = 0; i < n; i++) {
        Patient p;
        cout << "\nPatient " << i + 1 << " ID: "; cin >> p.id;
        cout << "Patient name: "; getline(cin >> ws, p.name);
        patients.add(p);
    }
    cout << "\nPatient list:\n"; patients.display();
    return 0;
}
