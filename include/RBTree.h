#pragma once

#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct BTreeNode {
    int value;
    Color color;
    BTreeNode* left;
    BTreeNode* right;
    BTreeNode* parent;
    BTreeNode(int val) : value(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BinaryTree {
private:
    BTreeNode* root;

    void rotateLeft(BTreeNode* &root, BTreeNode* x);
    void rotateRight(BTreeNode* &root, BTreeNode* y);
    void insertFixup(BTreeNode* &root, BTreeNode* z);
    void transplant(BTreeNode* &root, BTreeNode* u, BTreeNode* v);
    BTreeNode* treeMinimum(BTreeNode* node);
    void deleteFixup(BTreeNode* &root, BTreeNode* x, BTreeNode* xParent);
    void inorder(BTreeNode* node);

public:
    BinaryTree();
    void insert(int val);
    bool search(int val);
    void erase(int val);
    void inorderPrint();
};
