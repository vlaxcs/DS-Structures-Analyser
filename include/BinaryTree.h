#pragma once

struct BTreeNode {
    int value;
    BTreeNode* left;
    BTreeNode* right;
    BTreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    BTreeNode* root;

    BTreeNode* insert(BTreeNode* node, int val);
    bool search(BTreeNode* node, int val);
    BTreeNode* deleteNode(BTreeNode* node, int val);
    BTreeNode* findMin(BTreeNode* node);
    void inorder(BTreeNode* node);

public:
    BinaryTree() : root(nullptr) {}
    void insert(int val);
    bool search(int val);
    void deleteValue(int val);
    void inorderPrint();
};
