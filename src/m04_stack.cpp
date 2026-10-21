#include <iostream>
#include <string>
using namespace std;
struct Node
{
    string action;
    Node* next;
};
class Stack
{
    Node* top;
public:
    Stack()
    {
        top = NULL;
    }
    void push(string action)
    {
        Node* newNode = new Node;
        newNode->action = action;
        newNode->next = top;
        top = newNode;
    }
    void display()
    {
        Node* temp = top;
        if (top == NULL)
        {
            cout << "No actions saved.\n";
            return;
        }
        cout << "Actions (latest first):\n";
        while (temp != NULL)
        {
            cout << temp->action << endl;
            temp = temp->next;
        }
    }
    void undo()
    {
        if (top == NULL)
        {
            cout << "No action to undo.\n";
            return;
        }
        Node* temp = top;
        cout << "Undo action: " << top->action << endl;
        top = top->next;
        delete temp;
    }
    ~Stack()
    {
        while (top != NULL)
        {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }
};
int main()
{
    Stack s;
    int n;
    cout << "How many actions? ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string action;
        cout << "Enter action " << i + 1 << ": ";
        getline(cin >> ws, action);
        s.push(action);
    }
    cout << "\nSaved actions:\n";
    s.display();
    int choice;
    cout << "\nUndo latest action? (1 = Yes, 0 = No): ";
    cin >> choice;
    if (choice == 1)
    {
        s.undo();
    }
    cout << "\nActions after undo:\n";
    s.display();
    return 0;
}
