#include <iostream>
#include <string>
using namespace std;
const int SIZE = 10;
struct Doctor {
    int id;
    string name, specialization;
};
struct Node {
    Doctor data;
    Node* next;
    Node(Doctor d) {
        data = d;
        next = nullptr;
    }
};
class HashTable {
    Node* table[SIZE];
public:
    HashTable() {
        for (int i = 0; i < SIZE; i++)
            table[i] = nullptr;
    }
    int hash(int id) {
        return id % SIZE;
    }
    void add(Doctor d) {
        int index = hash(d.id);
        Node* temp = table[index];
        while (temp != nullptr) {
            if (temp->data.id == d.id) {
                temp->data = d;
                return;
            }
            temp = temp->next;
        }
        Node* newNode = new Node(d);
        newNode->next = table[index];
        table[index] = newNode;
    }
    void search(int id) {
        Node* temp = table[hash(id)];
        while (temp != nullptr) {
            if (temp->data.id == id) {
                cout << "Doctor Name: " << temp->data.name << endl;
                cout << "Specialization: "
                     << temp->data.specialization << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Doctor not found." << endl;
    }
    ~HashTable() {
        for (int i = 0; i < SIZE; i++) {
            Node* temp = table[i];
            while (temp != nullptr) {
                Node* old = temp;
                temp = temp->next;
                delete old;
            }
        }
    }
};
int main() {
    HashTable doctors;
    int n;
    cout << "How many doctors? ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        Doctor d;
        cout << "Doctor ID: ";
        cin >> d.id;
        cout << "Doctor Name: ";
        getline(cin >> ws, d.name);
        cout << "Specialization: ";
        getline(cin >> ws, d.specialization);
        doctors.add(d);
    }
    int id;
    cout << "\nEnter doctor ID to search: ";
    cin >> id;
    doctors.search(id);
    return 0;
}
