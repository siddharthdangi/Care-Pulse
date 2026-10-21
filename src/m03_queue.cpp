// MODULE 3: OPD waiting queue (First In, First Out)
#include <iostream>
#include <string>
using namespace std;
struct Patient { int id; string name; };
class Queue {
    struct Node { Patient data; Node* next; Node(Patient p): data(p), next(nullptr) {} };
    Node *front, *rear;
public:
    Queue(): front(nullptr), rear(nullptr) {}
    void add(Patient p) {
        Node* n = new Node(p);
        if (rear == nullptr) front = rear = n;
        else { rear->next = n; rear = n; }
    }
    bool serve() {
        if (front == nullptr) return false;
        Node* old = front;
        cout << "Now serving: " << old->data.name << " (ID " << old->data.id << ")\n";
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete old; return true;
    }
    void display() const {
        if (!front) { cout << "Queue is empty.\n"; return; }
        Node* cur = front;
        while (cur) { cout << cur->data.id << " - " << cur->data.name << '\n'; cur = cur->next; }
    }
    ~Queue() { while (serve()) {} }
};
int main() {
    Queue opd; int n;
    cout << "How many patients are waiting? "; cin >> n;
    for (int i=0;i<n;i++) {
        Patient p; cout << "Patient ID: "; cin >> p.id;
        cout << "Patient name: "; getline(cin >> ws, p.name); opd.add(p);
    }
    cout << "\nOPD waiting order:\n"; opd.display();
    cout << "\nServe the next patient? (1 Yes, 0 No): "; int yes; cin >> yes;
    if (yes == 1) opd.serve();
    cout << "Remaining queue:\n"; opd.display();
    return 0;
}
