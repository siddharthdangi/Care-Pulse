#include "CarePulseModules.h"

class PatientBST
{
    struct Node
    {
        int id;
        Node* l;
        Node* r;

        Node(int n) : id(n), l(NULL), r(NULL)
        {
        }
    };

    Node* root;

    Node* insert(Node* n, int id)
    {
        if (!n)
        {
            return new Node(id);
        }

        if (id < n->id)
        {
            n->l = insert(n->l, id);
        }
        else if (id > n->id)
        {
            n->r = insert(n->r, id);
        }

        return n;
    }

    bool find(Node* n, int id) const
    {
        if (!n)
        {
            return false;
        }

        if (n->id == id)
        {
            return true;
        }

        return id < n->id
            ? find(n->l, id)
            : find(n->r, id);
    }

    void clear(Node* n)
    {
        if (n)
        {
            clear(n->l);
            clear(n->r);
            delete n;
        }
    }

public:
    PatientBST() : root(NULL)
    {
    }

    ~PatientBST()
    {
        clear(root);
    }

    void reset(const HospitalData& d)
    {
        clear(root);
        root = NULL;

        for (int i = 0; i < d.patientCount; i++)
        {
            root = insert(root, d.patients[i].id);
        }
    }

    bool contains(int id) const
    {
        return find(root, id);
    }
};

static PatientBST tree;

void bstRebuild(const HospitalData& d)
{
    tree.reset(d);
}

bool bstContains(int id)
{
    return tree.contains(id);
}
