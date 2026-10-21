// MODULE 10: Appointment sorting using merge sort and searching by patient ID
#include <iostream>
#include <string>
using namespace std;

struct Appointment {
    int patientID;
    string patientName;
    string date; // Enter date as YYYYMMDD so text order matches date order.
    string time; // Enter time as HHMM, for example 0930.
};

void merge(Appointment a[], int left, int middle, int right) {
    Appointment temp[100];
    int i = left, j = middle + 1, k = left;

    while (i <= middle && j <= right) {
        if (a[i].date < a[j].date ||
            (a[i].date == a[j].date && a[i].time <= a[j].time))
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }
    while (i <= middle) temp[k++] = a[i++];
    while (j <= right) temp[k++] = a[j++];
    for (i = left; i <= right; i++) a[i] = temp[i];
}

void mergeSort(Appointment a[], int left, int right) {
    if (left >= right) return;
    int middle = (left + right) / 2;
    mergeSort(a, left, middle);
    mergeSort(a, middle + 1, right);
    merge(a, left, middle, right);
}

int binarySearch(Appointment a[], int n, int patientID) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int middle = (left + right) / 2;
        if (a[middle].patientID == patientID) return middle;
        if (a[middle].patientID < patientID) left = middle + 1;
        else right = middle - 1;
    }
    return -1;
}

int main() {
    Appointment a[100];
    int n;
    cout << "How many appointments? (maximum 100): "; cin >> n;
    if (n < 0) n = 0;
    if (n > 100) n = 100;

    for (int i=0;i<n;i++) {
        cout << "\nPatient ID: "; cin >> a[i].patientID;
        cout << "Patient name: "; getline(cin >> ws, a[i].patientName);
        cout << "Date (YYYYMMDD, e.g. 20261014): "; cin >> a[i].date;
        cout << "Time (HHMM, e.g. 0930): "; cin >> a[i].time;
    }

    mergeSort(a, 0, n - 1);
    cout << "\nAppointments sorted by date and time:\n";
    for (int i=0;i<n;i++)
        cout << a[i].date << " " << a[i].time << " | ID " << a[i].patientID
             << " | " << a[i].patientName << '\n';

    // Binary search needs the records sorted by the ID being searched.
    // Sort by patient ID first, then search.
    for (int i=0;i<n-1;i++)
        for (int j=0;j<n-i-1;j++)
            if (a[j].patientID > a[j+1].patientID) {
                Appointment temp=a[j]; a[j]=a[j+1]; a[j+1]=temp;
            }

    int wanted;
    cout << "\nEnter patient ID to search: "; cin >> wanted;
    int found = binarySearch(a, n, wanted);
    if (found >= 0) cout << "Found appointment for " << a[found].patientName
                         << " on " << a[found].date << " at " << a[found].time << '\n';
    else cout << "No appointment found for that ID.\n";
    return 0;
}
