#pragma once
#include "DataStructure.h"
#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct RBTreeNode {
    int value;
    Color color;
    RBTreeNode* left;
    RBTreeNode* right;
    RBTreeNode* parent;
    RBTreeNode(int val) : value(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree : public DataStructure {
private:
    RBTreeNode* root;

    void rotateLeft(RBTreeNode* &root, RBTreeNode* x);
    void rotateRight(RBTreeNode* &root, RBTreeNode* y);
    void insertFixup(RBTreeNode* &root, RBTreeNode* z);
    void transplant(RBTreeNode* &root, RBTreeNode* u, RBTreeNode* v);
    RBTreeNode* treeMinimum(RBTreeNode* node);
    void deleteFixup(RBTreeNode* &root, RBTreeNode* x, RBTreeNode* xParent);
    void inorder(RBTreeNode* node);

public:
    RBTree();
    void insert(int val);
    bool search(int val);
    void erase(int val);
    void inorderPrint();
};
