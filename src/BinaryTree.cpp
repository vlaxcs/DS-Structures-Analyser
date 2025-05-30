#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <chrono>
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

void BinaryTree::erase(int val) {
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