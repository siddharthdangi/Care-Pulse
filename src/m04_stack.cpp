// MODULE 4: Stack for recent hospital actions (Last In, First Out)
#include <iostream>
#include <string>
using namespace std;
class Stack {
    struct Node { string action; Node* next; Node(string a, Node* n): action(a), next(n) {} };
    Node* topNode;
public:
    Stack(): topNode(nullptr) {}
    void push(string action) { topNode = new Node(action, topNode); }
    bool undo() {
        if (!topNode) { cout << "There are no actions to undo.\n"; return false; }
        Node* old = topNode; cout << "Undo action: " << old->action << '\n';
        topNode = topNode->next; delete old; return true;
    }
    void display() const {
        if (!topNode) { cout << "No actions saved.\n"; return; }
        Node* cur = topNode; cout << "Most recent first:\n";
        while (cur) { cout << "- " << cur->action << '\n'; cur = cur->next; }
    }
    ~Stack() { while (topNode) { Node* old=topNode; topNode=topNode->next; delete old; } }
};
int main() {
    Stack actions; int n;
    cout << "How many actions do you want to record? "; cin >> n;
    for (int i=0;i<n;i++) {
        string action; cout << "Enter action " << i+1 << ": ";
        getline(cin >> ws, action); actions.push(action);
    }
    actions.display();
    cout << "\nUndo the latest action? (1 Yes, 0 No): "; int choice; cin >> choice;
    if (choice == 1) actions.undo();
    cout << "\nActions after undo:\n"; actions.display();
    return 0;
}
