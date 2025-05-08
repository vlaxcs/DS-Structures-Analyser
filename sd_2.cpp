///INSTRUCTIUNI
///1 pentru introducerea unui numar in binary tree
///2 pentru cautarea unui numar( cout 1 for found, 0 for not found)
///3 pentru scoaterea unui numar din binary tree
///pentru input, un fisier "input.txt" cu un string de forma (nr comanda, nr asupra caruia se efectueaza comanda) * n
#include <iostream>
#include <fstream>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int val) {
    if (!root) return new Node(val);
    if (val < (*root).value)
        (*root).left = insert((*root).left, val);
    else if (val > (*root).value)
        (*root).right = insert((*root).right, val);
    return root;
}

bool search(Node* root, int val) {
    if (!root) return false;
    if (val == (*root).value) return true;
    return val < (*root).value ? search((*root).left, val) : search((*root).right, val);
}

Node* findMin(Node* root) {
    while (root && (*root).left)
        root = (*root).left;
    return root;
}

Node* deleteNode(Node* root, int val) {
    if (!root) return nullptr;
    if (val < (*root).value)
        (*root).left = deleteNode((*root).left, val);
    else if (val > (*root).value)
        (*root).right = deleteNode((*root).right, val);
    else {
        if (!(*root).left) {
            Node* temp = (*root).right;
            delete root;
            return temp;
        } else if (!(*root).right) {
            Node* temp = (*root).left;
            delete root;
            return temp;
        }
        Node* temp = findMin((*root).right);
        (*root).value = (*temp).value;
        (*root).right = deleteNode((*root).right, (*temp).value);
    }
    return root;
}

void inorder(Node* root) {
    if (!root) return;
    inorder((*root).left);
    cout << (*root).value << " ";
    inorder((*root).right);
}

int main() {
    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Error opening input file.\n";
        return 1;
    }

    Node* root = nullptr;
    int a, b;
    while (fin >> a >> b) {
        if (a == 1) {
            root = insert(root, b);
        } else if (a == 2) {
            cout << (search(root, b) ? 1 : 0) << " ";
        } else if (a == 3) {
            root = deleteNode(root, b);
        }
    }

    cout << "\n";
    inorder(root);
    cout << "\n";

    return 0;
}
