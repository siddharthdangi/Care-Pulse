// MODULE 3: OPD waiting queue (First In, First Out)
#include <iostream>
#include <string>
using namespace std;

struct Patient {
    int id;
    string name;
};

class Queue {
    struct Node {
        Patient data;
        Node* next;
    };

    Node *front, *rear;

public:
    Queue() {
        front = rear = nullptr;
    }

    void add(Patient p) {
        Node* n = new Node{p, nullptr};

        if (rear == nullptr)
            front = rear = n;
        else {
            rear->next = n;
            rear = n;
        }
    }

    void serve() {
        if (front == nullptr) {
            cout << "Queue is empty.\n";
            return;
        }

        Node* temp = front;
        cout << "Now serving: " << temp->data.name;
        cout << " (ID " << temp->data.id << ")\n";

        front = front->next;

        if (front == nullptr)
            rear = nullptr;

        delete temp;
    }

    void display() {
        if (front == nullptr) {
            cout << "Queue is empty.\n";
            return;
        }

        Node* temp = front;

        while (temp != nullptr) {
            cout << temp->data.id << " - ";
            cout << temp->data.name << endl;
            temp = temp->next;
        }
    }

    ~Queue() {
        while (front != nullptr) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

int main() {
    Queue opd;
    int n;

    cout << "How many patients are waiting? ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        Patient p;

        cout << "Patient ID: ";
        cin >> p.id;

        cout << "Patient name: ";
        getline(cin >> ws, p.name);

        opd.add(p);
    }

    cout << "\nOPD waiting order:\n";
    opd.display();

    int yes;
    cout << "\nServe the next patient? (1 Yes, 0 No): ";
    cin >> yes;

    if (yes == 1)
        opd.serve();

    cout << "Remaining queue:\n";
    opd.display();

    return 0;
}
