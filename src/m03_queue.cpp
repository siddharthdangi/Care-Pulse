#include "CarePulseModules.h"

class OPDLinkedQueue
{
    struct Node
    {
        int id;
        Node* next;

        Node(int n) : id(n), next(NULL)
        {
        }
    };

    Node* frontNode;
    Node* rearNode;
    int total;

public:
    OPDLinkedQueue() : frontNode(NULL), rearNode(NULL), total(0)
    {
    }

    ~OPDLinkedQueue()
    {
        clear();
    }

    void clear()
    {
        while (frontNode)
        {
            Node* t = frontNode;
            frontNode = frontNode->next;
            delete t;
        }

        rearNode = NULL;
        total = 0;
    }

    bool contains(int id) const
    {
        for (Node* n = frontNode; n; n = n->next)
        {
            if (n->id == id)
            {
                return true;
            }
        }

        return false;
    }

    void add(int id)
    {
        if (contains(id))
        {
            return;
        }

        Node* n = new Node(id);

        if (!rearNode)
        {
            frontNode = rearNode = n;
        }
        else
        {
            rearNode->next = n;
            rearNode = n;
        }

        total++;
    }

    int serve()
    {
        if (!frontNode)
        {
            return -1;
        }

        Node* t = frontNode;
        int id = t->id;

        frontNode = frontNode->next;

        if (!frontNode)
        {
            rearNode = NULL;
        }

        delete t;
        total--;

        return id;
    }

    void remove(int id)
    {
        Node* n = frontNode;
        Node* prev = NULL;

        while (n)
        {
            if (n->id == id)
            {
                if (prev)
                {
                    prev->next = n->next;
                }
                else
                {
                    frontNode = n->next;
                }

                if (rearNode == n)
                {
                    rearNode = prev;
                }

                delete n;
                total--;

                return;
            }

            prev = n;
            n = n->next;
        }
    }

    int count() const
    {
        return total;
    }

    void display(const HospitalData& d) const
    {
        if (!frontNode)
        {
            cout << "OPD queue is empty.\n";
            return;
        }

        int pos = 1;

        for (Node* n = frontNode; n; n = n->next)
        {
            int i = findPatientIndex(d, n->id);

            if (i >= 0)
            {
                cout << pos++ << ". "
                     << d.patients[i].name
                     << " (ID " << n->id << ")\n";
            }
        }
    }
};

static OPDLinkedQueue opd;

void opdRebuild(const HospitalData& d)
{
    opd.clear();

    int ids[MAX_RECORDS], n = 0;

    for (int i = 0; i < d.patientCount; i++)
    {
        if (d.patients[i].status == "Waiting for OPD")
        {
            ids[n++] = i;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (d.patients[ids[j]].queueOrder
                < d.patients[ids[i]].queueOrder)
            {
                int t = ids[i];
                ids[i] = ids[j];
                ids[j] = t;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        opd.add(d.patients[ids[i]].id);
    }
}

bool opdContains(int id)
{
    return opd.contains(id);
}

int opdCount()
{
    return opd.count();
}

void opdAdd(int id)
{
    opd.add(id);
}

int opdServe()
{
    return opd.serve();
}

void opdRemove(int id)
{
    opd.remove(id);
}

void opdDisplay(const HospitalData& d)
{
    opd.display(d);
}

void addToOPD(HospitalData& d, int id, const string& user)
{
    int i = findPatientIndex(d, id);

    if (i < 0)
    {
        cout << "Register the patient first.\n";
        return;
    }

    if (opdContains(id))
    {
        cout << "Patient is already waiting in OPD.\n";
        return;
    }

    pushUndo(d, "Add patient to OPD");

    d.patients[i].status = "Waiting for OPD";
    d.patients[i].queueOrder = d.nextArrival++;
    d.patients[i].emergencyOrder = 0;

    opdAdd(id);
    saveAll(d);

    auditAction(
        user,
        "Staff",
        "Added patient ID " + to_string(id) + " to OPD"
    );

    cout << "Added to OPD. Estimated wait: about "
         << opdCount() * d.averageConsultMinutes
         << " minutes.\n";
}

void serveOPD(HospitalData& d, const string& user)
{
    if (opdCount() == 0)
    {
        cout << "OPD queue is empty.\n";
        return;
    }

    pushUndo(d, "Serve OPD patient");

    int id = opdServe();
    int i = findPatientIndex(d, id);

    if (i >= 0)
    {
        d.patients[i].status = "In consultation";
    }

    saveAll(d);

    auditAction(
        user,
        "Staff",
        "Served OPD patient ID " + to_string(id)
    );

    cout << "Now serving patient ID " << id << ".\n";
}
