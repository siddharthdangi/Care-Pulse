#include <iostream>
#include <string>
using namespace std;
struct Patient {
    int id;
    string name;
};
struct Node {
    Patient p;
    Node *left, *right;
    Node(Patient x) {
        p = x;
        left = right = nullptr;
    }
};
class BST {
    Node *root;
    Node* insert(Node *root, Patient p) {
        if (root == nullptr)
            return new Node(p);
        if (p.id < root->p.id)
            root->left = insert(root->left, p);
        else if (p.id > root->p.id)
            root->right = insert(root->right, p);
        else
            root->p = p;
        return root;
    }
    void display(Node *root) {
        if (root == nullptr)
            return;
        display(root->left);
        cout << root->p.id << " - " << root->p.name << endl;
        display(root->right);
    }
    Node* search(Node *root, int id) {
        if (root == nullptr || root->p.id == id)
            return root;
        if (id < root->p.id)
            return search(root->left, id);
        return search(root->right, id);
    }
public:
    BST() {
        root = nullptr;
    }
    void add(Patient p) {
        root = insert(root, p);
    }
    void displayPatients() {
        display(root);
    }
    void searchPatient(int id) {
        Node *result = search(root, id);
        if (result != nullptr)
            cout << "Patient found: " << result->p.name
                 << ", ID: " << result->p.id << endl;
        else
            cout << "Patient not found." << endl;
    }
};
int main() {
    BST tree;
    int n;
    cout << "Enter number of patients: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        Patient p;
        cout << "Enter patient ID: ";
        cin >> p.id;
        cout << "Enter patient name: ";
        getline(cin >> ws, p.name);
        tree.add(p);
    }
    cout << "\nPatients sorted by ID:\n";
    tree.displayPatients();
    int id;
    cout << "\nEnter ID to search: ";
    cin >> id;
    tree.searchPatient(id);
    return 0;
}
