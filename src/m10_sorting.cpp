// MODULE 10: Appointment sorting using merge sort and searching by patient ID
#include <iostream>
#include <string>
using namespace std;

struct Appointment {
    int patientID;
    string patientName, date, time;
};

void merge(Appointment a[], int l, int m, int r) {
    Appointment temp[100];
    int i = l, j = m + 1, k = l;

    while (i <= m && j <= r) {
        if (a[i].date < a[j].date ||
            (a[i].date == a[j].date && a[i].time <= a[j].time))
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= m) temp[k++] = a[i++];
    while (j <= r) temp[k++] = a[j++];

    for (i = l; i <= r; i++)
        a[i] = temp[i];
}

void mergeSort(Appointment a[], int l, int r) {
    if (l >= r) return;

    int m = (l + r) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);
    merge(a, l, m, r);
}

void sortByID(Appointment a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j].patientID > a[j + 1].patientID) {
                Appointment temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
}

int binarySearch(Appointment a[], int n, int id) {
    int l = 0, r = n - 1;

    while (l <= r) {
        int m = (l + r) / 2;

        if (a[m].patientID == id) return m;
        if (a[m].patientID < id) l = m + 1;
        else r = m - 1;
    }

    return -1;
}

int main() {
    Appointment a[100];
    int n;

    cout << "How many appointments (max 100)? ";
    cin >> n;

    if (n < 1 || n > 100) {
        cout << "Invalid number of appointments.\n";
        return 0;
    }

    for (int i = 0; i < n; i++) {
        cout << "\nPatient ID: ";
        cin >> a[i].patientID;

        cout << "Patient name: ";
        getline(cin >> ws, a[i].patientName);

        cout << "Date (YYYYMMDD): ";
        cin >> a[i].date;

        cout << "Time (HHMM): ";
        cin >> a[i].time;
    }

    mergeSort(a, 0, n - 1);

    cout << "\nAppointments sorted by date and time:\n";

    for (int i = 0; i < n; i++)
        cout << a[i].date << " " << a[i].time
             << " | ID " << a[i].patientID
             << " | " << a[i].patientName << '\n';

    sortByID(a, n);

    int id;
    cout << "\nEnter patient ID to search: ";
    cin >> id;

    int pos = binarySearch(a, n, id);

    if (pos != -1)
        cout << "Found appointment for " << a[pos].patientName
             << " on " << a[pos].date
             << " at " << a[pos].time << '\n';
    else
        cout << "No appointment found for that ID.\n";

    return 0;
}
