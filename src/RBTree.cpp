#include <iostream>
#include <fstream>
#include <stack>
#include <chrono>
#include "RBTree.h"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto start = chrono::high_resolution_clock::now(); 
    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Error opening input file.\n";
        return 1;
    }

    BinaryTree tree;
    string command;
    int value;
    while (fin >> command >> value) {
        if (command == "insert") {
            tree.insert(value);
        } else if (command == "search") {
            cout << (tree.search(value) ? 1 : 0) << " ";
        } else if (command == "delete") {
            tree.erase(value);
        }
    }
    auto end = chrono::high_resolution_clock::now();

    cout << "\n";
    tree.inorderPrint();
    cout << "\n";
    chrono::duration<double> elapsed = end - start;
    cout << "Execution time: " << elapsed.count() << " seconds\n";

    return 0;
}

BinaryTree::BinaryTree() : root(nullptr) {}

void BinaryTree::rotateLeft(BTreeNode* &root, BTreeNode* x) {
    BTreeNode* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void BinaryTree::rotateRight(BTreeNode* &root, BTreeNode* y) {
    BTreeNode* x = y->left;
    y->left = x->right;
    if (x->right) x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent) root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void BinaryTree::insertFixup(BTreeNode* &root, BTreeNode* z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            BTreeNode* y = z->parent->parent->right;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateRight(root, z->parent->parent);
            }
        } else {
            BTreeNode* y = z->parent->parent->left;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateLeft(root, z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void BinaryTree::transplant(BTreeNode* &root, BTreeNode* u, BTreeNode* v) {
    if (!u->parent)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v) v->parent = u->parent;
}

BTreeNode* BinaryTree::treeMinimum(BTreeNode* node) {
    while (node->left) node = node->left;
    return node;
}

void BinaryTree::deleteFixup(BTreeNode* &root, BTreeNode* x, BTreeNode* xParent) {
    while ((x != root) && (!x || x->color == BLACK)) {
        if (x == xParent->left) {
            BTreeNode* w = xParent->right;
            if (w && w->color == RED) {
                w->color = BLACK;
                xParent->color = RED;
                rotateLeft(root, xParent);
                w = xParent->right;
            }
            if ((!w->left || w->left->color == BLACK) && (!w->right || w->right->color == BLACK)) {
                w->color = RED;
                x = xParent;
                xParent = x->parent;
            } else {
                if (!w->right || w->right->color == BLACK) {
                    if (w->left) w->left->color = BLACK;
                    w->color = RED;
                    rotateRight(root, w);
                    w = xParent->right;
                }
                w->color = xParent->color;
                xParent->color = BLACK;
                if (w->right) w->right->color = BLACK;
                rotateLeft(root, xParent);
                x = root;
                break;
            }
        } else {
            BTreeNode* w = xParent->left;
            if (w && w->color == RED) {
                w->color = BLACK;
                xParent->color = RED;
                rotateRight(root, xParent);
                w = xParent->left;
            }
            if ((!w->right || w->right->color == BLACK) && (!w->left || w->left->color == BLACK)) {
                w->color = RED;
                x = xParent;
                xParent = x->parent;
            } else {
                if (!w->left || w->left->color == BLACK) {
                    if (w->right) w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft(root, w);
                    w = xParent->left;
                }
                w->color = xParent->color;
                xParent->color = BLACK;
                if (w->left) w->left->color = BLACK;
                rotateRight(root, xParent);
                x = root;
                break;
            }
        }
    }
    if (x) x->color = BLACK;
}

void BinaryTree::inorder(BTreeNode* node) {
    if (!node) return;
    inorder(node->left);
    cout << node->value << ' ';
    inorder(node->right);
}

void BinaryTree::insert(int val) {
    BTreeNode* z = new BTreeNode(val);
    BTreeNode* y = nullptr;
    BTreeNode* x = root;

    while (x) {
        y = x;
        if (z->value < x->value) x = x->left;
        else if (z->value > x->value) x = x->right;
        else {
            delete z;
            return;
        }
    }

    z->parent = y;
    if (!y)
        root = z;
    else if (z->value < y->value)
        y->left = z;
    else
        y->right = z;

    insertFixup(root, z);
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
    BTreeNode* z = root;
    while (z && z->value != val) {
        if (val < z->value) z = z->left;
        else z = z->right;
    }
    if (!z) return;

    BTreeNode* y = z;
    Color yOriginalColor = y->color;
    BTreeNode* x;
    BTreeNode* xParent;

    if (!z->left) {
        x = z->right;
        xParent = z->parent;
        transplant(root, z, z->right);
    } else if (!z->right) {
        x = z->left;
        xParent = z->parent;
        transplant(root, z, z->left);
    } else {
        y = treeMinimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x) x->parent = y;
            xParent = y;
        } else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
            xParent = y->parent;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;
    if (yOriginalColor == BLACK)
        deleteFixup(root, x, xParent);
}

void BinaryTree::inorderPrint() {
    inorder(root);
}
