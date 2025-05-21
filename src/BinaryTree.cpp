/// INSTRUCTIUNI
/// 1 pentru introducerea unui numar in binary tree
/// 2 pentru cautarea unui numar (cout 1 for found, 0 for not found)
/// 3 pentru scoaterea unui numar din binary tree
/// pentru input, un fisier "input.txt" cu un string de forma (nr comanda, nr asupra caruia se efectueaza comanda) * n
#include <iostream>
#include <fstream>
#include <stack>
#include "BinaryTree.h"
using namespace std;

BTreeNode* BinaryTree::insert(BTreeNode* node, int val) {
    if (!node) return new BTreeNode(val);
    if (val < (*node).value)
        (*node).left = insert((*node).left, val);
    else if (val > (*node).value)
        (*node).right = insert((*node).right, val);
    return node;
}

bool BinaryTree::search(BTreeNode* node, int val) {
    if (!node) return false;
    if (val == (*node).value) return true;
    return val < (*node).value ? search((*node).left, val) : search((*node).right, val);
}

BTreeNode* BinaryTree::findMin(BTreeNode* node) {
    while (node && (*node).left)
        node = (*node).left;
    return node;
}

void BinaryTree::insert(int val) {
    BTreeNode* newNode = new BTreeNode(val);
    if (!root) {
        root = newNode;
        return;
    }

    BTreeNode* curr = root;
    BTreeNode* parent = nullptr;
    while (curr) {
        parent = curr;
        if (val < curr->value)
            curr = curr->left;
        else if (val > curr->value)
            curr = curr->right;
        else {
            delete newNode;
            return;
        }
    }

    if (val < parent->value)
        parent->left = newNode;
    else
        parent->right = newNode;
}


bool BinaryTree::search(int val) {
    BTreeNode* curr = root;
    while (curr) {
        if (val == curr->value)
            return true;
        else if (val < curr->value)
            curr = curr->left;
        else
            curr = curr->right;
    }
    return false;
}

void BinaryTree::deleteValue(int val) {
    BTreeNode* parent = nullptr;
    BTreeNode* curr = root;

    while (curr && curr->value != val) {
        parent = curr;
        if (val < curr->value)
            curr = curr->left;
        else
            curr = curr->right;
    }

    if (!curr) return;

    if (curr->left && curr->right) {
        BTreeNode* successorParent = curr;
        BTreeNode* successor = curr->right;
        while (successor->left) {
            successorParent = successor;
            successor = successor->left;
        }

        curr->value = successor->value;
        curr = successor;
        parent = successorParent;
    }

    BTreeNode* child = (curr->left) ? curr->left : curr->right;

    if (!parent)
        root = child;
    else if (parent->left == curr)
        parent->left = child;
    else
        parent->right = child;

    delete curr;
}

void BinaryTree::inorderPrint() {
    std::stack<BTreeNode*> st;
    BTreeNode* curr = root;

    while (curr || !st.empty()) {

        while (curr) {
            st.push(curr);
            curr = curr->left;
        }

        curr = st.top();
        st.pop();
        std::cout << curr->value << ' ';

        curr = curr->right;
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Error opening input file.\n";
        return 1;
    }

    BinaryTree tree;
    int a, b;
    while (fin >> a >> b) {
        if (a == 1) {
            tree.insert(b);
        } else if (a == 2) {
            cout << (tree.search(b) ? 1 : 0) << " ";
        } else if (a == 3) {
            tree.deleteValue(b);
        }
    }

    cout << "\n";
    tree.inorderPrint();
    cout << "\n";

    return 0;
}