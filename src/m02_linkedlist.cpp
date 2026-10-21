// MODULE 2: Linked List of patient records
#include <iostream>
#include <string>
using namespace std;

struct Patient {
    int id;
    string name;
};

struct Node {
    Patient data;
    Node* next;
};

class LinkedList {
    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }

    void add(Patient p) {
        Node* n = new Node{p, nullptr};

        if (head == nullptr)
            head = n;
        else {
            Node* temp = head;
            while (temp->next != nullptr)
                temp = temp->next;
            temp->next = n;
        }
    }

    void display() {
        Node* temp = head;

        if (temp == nullptr) {
            cout << "No patients recorded.\n";
            return;
        }

        while (temp != nullptr) {
            cout << "ID: " << temp->data.id;
            cout << ", Name: " << temp->data.name << endl;
            temp = temp->next;
        }
    }

    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList patients;
    int n;

    cout << "How many patients? ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        Patient p;

        cout << "Enter patient ID: ";
        cin >> p.id;

        cout << "Enter patient name: ";
        getline(cin >> ws, p.name);

        patients.add(p);
    }

    cout << "\nPatient List:\n";
    patients.display();

    return 0;
}
