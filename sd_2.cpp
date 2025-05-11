/// INSTRUCTIUNI
/// 1 pentru introducerea unui numar in binary tree
/// 2 pentru cautarea unui numar (cout 1 for found, 0 for not found)
/// 3 pentru scoaterea unui numar din binary tree
/// pentru input, un fisier "input.txt" cu un string de forma (nr comanda, nr asupra caruia se efectueaza comanda) * n
#include <iostream>
#include <fstream>
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

BTreeNode* BinaryTree::deleteNode(BTreeNode* node, int val) {
    if (!node) return nullptr;
    if (val < (*node).value)
        (*node).left = deleteNode((*node).left, val);
    else if (val > (*node).value)
        (*node).right = deleteNode((*node).right, val);
    else {
        if (!(*node).left) {
            BTreeNode* temp = (*node).right;
            delete node;
            return temp;
        } else if (!(*node).right) {
            BTreeNode* temp = (*node).left;
            delete node;
            return temp;
        }
        BTreeNode* temp = findMin((*node).right);
        (*node).value = (*temp).value;
        (*node).right = deleteNode((*node).right, (*temp).value);
    }
    return node;
}

void BinaryTree::inorder(BTreeNode* node) {
    if (!node) return;
    inorder((*node).left);
    cout << (*node).value << " ";
    inorder((*node).right);
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
            delete newNode;  // value already exists
            return;
        }
    }

    if (val < parent->value)
        parent->left = newNode;
    else
        parent->right = newNode;
}


bool BinaryTree::search(int val) {
    return search(root, val);
}

void BinaryTree::deleteValue(int val) {
    root = deleteNode(root, val);
}

void BinaryTree::inorderPrint() {
    inorder(root);
}

int main() {
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
