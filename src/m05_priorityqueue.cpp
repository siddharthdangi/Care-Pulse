#include "CarePulseModules.h"

class EmergencyHeap
{
    struct Item
    {
        int id, severity, order;
    };

    Item heap[MAX_RECORDS];
    int n;

    bool higher(const Item& a, const Item& b) const
    {
        return a.severity != b.severity
            ? a.severity > b.severity
            : a.order < b.order;
    }

    void swapItem(int a, int b)
    {
        Item t = heap[a];
        heap[a] = heap[b];
        heap[b] = t;
    }

    void up(int i)
    {
        while (i > 0)
        {
            int p = (i - 1) / 2;

            if (higher(heap[p], heap[i]))
            {
                break;
            }

            swapItem(p, i);
            i = p;
        }
    }

    void down(int i)
    {
        while (true)
        {
            int l = 2 * i + 1;
            int r = 2 * i + 2;
            int b = i;

            if (l < n && higher(heap[l], heap[b]))
            {
                b = l;
            }

            if (r < n && higher(heap[r], heap[b]))
            {
                b = r;
            }

            if (b == i)
            {
                break;
            }

            swapItem(i, b);
            i = b;
        }
    }

public:
    EmergencyHeap() : n(0)
    {
    }

    void clear()
    {
        n = 0;
    }

    bool contains(int id) const
    {
        for (int i = 0; i < n; i++)
        {
            if (heap[i].id == id)
            {
                return true;
            }
        }

        return false;
    }

    void add(int id, int s, int o)
    {
        if (n >= MAX_RECORDS || contains(id))
        {
            return;
        }

        heap[n].id = id;
        heap[n].severity = s;
        heap[n].order = o;

        up(n++);
    }

    int serve()
    {
        if (!n)
        {
            return -1;
        }

        int id = heap[0].id;
        heap[0] = heap[--n];

        if (n)
        {
            down(0);
        }

        return id;
    }

    void remove(int id)
    {
        for (int i = 0; i < n; i++)
        {
            if (heap[i].id == id)
            {
                heap[i] = heap[--n];

                if (i < n)
                {
                    up(i);
                    down(i);
                }

                return;
            }
        }
    }

    int count() const
    {
        return n;
    }

    void display(const HospitalData& d) const
    {
        if (!n)
        {
            cout << "No emergency cases waiting.\n";
            return;
        }

        Item copy[MAX_RECORDS];
        int c = n;

        for (int i = 0; i < n; i++)
        {
            copy[i] = heap[i];
        }

        cout << "Emergency queue (higher severity first):\n";

        for (int k = 0; k < c; k++)
        {
            int best = 0;

            for (int j = 1; j < n; j++)
            {
                if (higher(heap[j], heap[best]))
                {
                    best = j;
                }
            }

            int id = heap[best].id;
            int pi = findPatientIndex(d, id);

            if (pi >= 0)
            {
                cout << d.patients[pi].name
                     << " | ID " << id
                     << " | " << severityName(d.patients[pi].severity)
                     << '\n';
            }

            const_cast<EmergencyHeap*>(this)->remove(id);
        }

        for (int i = 0; i < c; i++)
        {
            const_cast<EmergencyHeap*>(this)->add(
                copy[i].id,
                copy[i].severity,
                copy[i].order
            );
        }
    }
};

static EmergencyHeap emergencies;

void emergencyRebuild(const HospitalData& d)
{
    emergencies.clear();

    for (int i = 0; i < d.patientCount; i++)
    {
        if (d.patients[i].status == "Waiting for emergency")
        {
            emergencies.add(
                d.patients[i].id,
                d.patients[i].severity,
                d.patients[i].emergencyOrder
            );
        }
    }
}

bool emergencyContains(int id)
{
    return emergencies.contains(id);
}

int emergencyCount()
{
    return emergencies.count();
}

void emergencyAdd(const HospitalData& d, int id)
{
    int i = findPatientIndex(d, id);

    if (i >= 0)
    {
        emergencies.add(
            id,
            d.patients[i].severity,
            d.patients[i].emergencyOrder
        );
    }
}

int emergencyServe()
{
    return emergencies.serve();
}

void emergencyRemove(int id)
{
    emergencies.remove(id);
}

void emergencyDisplay(const HospitalData& d)
{
    emergencies.display(d);
}

void addEmergencyCase(HospitalData& d, int id, const string& user)
{
    int i = findPatientIndex(d, id);

    if (i < 0)
    {
        cout << "Register the patient first.\n";
        return;
    }

    if (emergencyContains(id))
    {
        cout << "Already in emergency queue.\n";
        return;
    }

    int s;

    cout << "Severity (1 Stable, 2 Moderate, 3 Severe, 4 Critical): ";
    cin >> s;

    if (s < 1 || s > 4)
    {
        cout << "Invalid severity.\n";
        return;
    }

    pushUndo(d, "Add emergency case");

    opdRemove(id);

    d.patients[i].severity = s;
    d.patients[i].status = "Waiting for emergency";
    d.patients[i].emergencyOrder = d.nextArrival++;

    emergencyAdd(d, id);

    saveAll(d);

    auditAction(
        user,
        "Staff",
        "Added emergency case ID " + to_string(id)
    );

    cout << "Emergency case added. Critical cases are prioritized; "
         << "equal severity follows arrival order.\n";
}

void serveEmergencyCase(HospitalData& d, const string& user)
{
    if (!emergencyCount())
    {
        cout << "No emergency cases waiting.\n";
        return;
    }

    pushUndo(d, "Serve emergency case");

    int id = emergencyServe();
    int i = findPatientIndex(d, id);

    if (i >= 0)
    {
        d.patients[i].status = "Emergency case attended";
    }

    saveAll(d);

    auditAction(
        user,
        "Staff",
        "Served emergency case ID " + to_string(id)
    );

    cout << "Emergency queue next case served: patient ID "
         << id << ". Clinical decisions remain with medical staff.\n";
}
