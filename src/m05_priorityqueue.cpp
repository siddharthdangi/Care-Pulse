// MODULE 5: Emergency priority queue using a simple binary heap
#include <iostream>
#include <string>
using namespace std;

struct Patient {
    int id;
    string name;
    int severity; // 1 Stable, 2 Moderate, 3 Severe, 4 Critical
    int arrivalOrder;
};

class PriorityQueue {
    Patient heap[100];
    int count;
    int nextOrder;

    bool higherPriority(int a, int b) const {
        if (heap[a].severity != heap[b].severity)
            return heap[a].severity > heap[b].severity;
        return heap[a].arrivalOrder < heap[b].arrivalOrder;
    }

    void swapPatients(int a, int b) {
        Patient temp = heap[a];
        heap[a] = heap[b];
        heap[b] = temp;
    }

public:
    PriorityQueue() : count(0), nextOrder(0) {}

    void add(Patient p) {
        if (count == 100) { cout << "Queue is full.\n"; return; }
        int child = count;
        p.arrivalOrder = nextOrder++;
        heap[child] = p;
        count++;

        // Move the new patient up while their severity is higher.
        while (child > 0) {
            int parent = (child - 1) / 2;
            if (higherPriority(parent, child)) break;
            swapPatients(parent, child);
            child = parent;
        }
    }

    bool serveNext() {
        if (count == 0) { cout << "No patients waiting.\n"; return false; }
        cout << "Serve: " << heap[0].name << " (ID " << heap[0].id << ")\n";
        heap[0] = heap[count - 1];
        count--;

        // Move the most severe remaining patient to the top.
        int parent = 0;
        while (true) {
            int left = 2 * parent + 1;
            int right = 2 * parent + 2;
            int largest = parent;
            if (left < count && higherPriority(left, largest)) largest = left;
            if (right < count && higherPriority(right, largest)) largest = right;
            if (largest == parent) break;
            swapPatients(parent, largest);
            parent = largest;
        }
        return true;
    }

    void display() const {
        cout << "\nPatients in heap order (highest priority first at the top):\n";
        for (int i=0;i<count;i++)
            cout << heap[i].name << " (ID " << heap[i].id << "), severity " << heap[i].severity << '\n';
        if (count == 0) cout << "No patients in queue.\n";
    }
};

int main() {
    PriorityQueue emergency;
    int n;
    cout << "How many emergency patients? "; cin >> n;
    if (n > 100) n = 100;
    for (int i=0;i<n;i++) {
        Patient p;
        cout << "\nPatient ID: "; cin >> p.id;
        cout << "Patient name: "; getline(cin >> ws, p.name);
        cout << "Severity (1 Stable, 2 Moderate, 3 Severe, 4 Critical): "; cin >> p.severity;
        if (p.severity < 1 || p.severity > 4) { cout << "Invalid severity; using 1 (Stable).\n"; p.severity=1; }
        emergency.add(p);
    }
    emergency.display();
    cout << "\nServe the highest-priority patient? (1 Yes, 0 No): ";
    int choice; cin >> choice;
    if (choice == 1) emergency.serveNext();
    emergency.display();
    return 0;
}
