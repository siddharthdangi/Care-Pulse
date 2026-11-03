#include "CarePulseModules.h"

class UndoStack
{
    struct Node
    {
        HospitalData snapshot;
        string action;
        Node* next;

        Node(const HospitalData& d, const string& a, Node* n)
            : snapshot(d), action(a), next(n)
        {
        }
    };

    Node* topNode;
    int total;

public:
    UndoStack() : topNode(NULL), total(0)
    {
    }

    ~UndoStack()
    {
        clear();
    }

    void clear()
    {
        while (topNode)
        {
            Node* t = topNode;
            topNode = topNode->next;
            delete t;
        }

        total = 0;
    }

    void push(const HospitalData& d, const string& a)
    {
        topNode = new Node(d, a, topNode);
        total++;

        if (total > MAX_UNDO)
        {
            Node* n = topNode;

            while (n->next && n->next->next)
            {
                n = n->next;
            }

            if (n->next)
            {
                delete n->next;
                n->next = NULL;
                total--;
            }
        }
    }

    bool pop(HospitalData& d, string& a)
    {
        if (!topNode)
        {
            return false;
        }

        Node* t = topNode;

        d = t->snapshot;
        a = t->action;

        topNode = t->next;

        delete t;
        total--;

        return true;
    }

    void display() const
    {
        if (!topNode)
        {
            cout << "No actions available to undo.\n";
            return;
        }

        cout << "Recent reversible actions (newest first):\n";

        for (Node* n = topNode; n; n = n->next)
        {
            cout << "- " << n->action << '\n';
        }
    }
};

static UndoStack undoStack;

void pushUndo(const HospitalData& d, const string& a)
{
    undoStack.push(d, a);
}

bool undoLast(HospitalData& d, string& a)
{
    return undoStack.pop(d, a);
}

void clearUndo()
{
    undoStack.clear();
}

void showUndoHistory()
{
    undoStack.display();
}
