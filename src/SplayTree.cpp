#include "SplayTree.h"

SplayTree::SplayTree() {
    root = nullptr;
}

SplayNode* SplayTree::newSplayNode(float value) {
    SplayNode* node = new SplayNode;
    node->value = value;
    node->left = node->right = nullptr;
    return node;
}

SplayNode* SplayTree::zagRot(SplayNode* x) {
    SplayNode* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

SplayNode* SplayTree::zigRot(SplayNode* x) {
    SplayNode* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

SplayNode* SplayTree::splay(SplayNode* root, float value) {
    if (root == nullptr || root->value == value)
        return root;

    if (root->value > value) {
        if (root->left == nullptr)
            return root;

        if (root->left->value > value) {
            root->left->left = splay(root->left->left, value);
            root = zigRot(root);
        } else if (root->left->value < value) {
            root->left->right = splay(root->left->right, value);
            if (root->left->right != nullptr)
                root->left = zagRot(root->left);
        }

        return (root->left == nullptr) ? root : zigRot(root);
    } else {
        if (root->right == nullptr)
            return root;

        if (root->right->value > value) {
            root->right->left = splay(root->right->left, value);
            if (root->right->left != nullptr)
                root->right = zigRot(root->right);
        } else if (root->right->value < value) {
            root->right->right = splay(root->right->right, value);
            root = zagRot(root);
        }

        return (root->right == nullptr) ? root : zagRot(root);
    }
}

SplayNode* SplayTree::insert(const float value) {
    if (root == nullptr) {
        root = newSplayNode(value);
        return root;
    }

    root = splay(root, value);

    if (root->value == value)
        return root;

    SplayNode* node = newSplayNode(value);
    if (root->value > value) {
        node->right = root;
        node->left = root->left;
        root->left = nullptr;
    } else {
        node->left = root;
        node->right = root->right;
        root->right = nullptr;
    }

    root = node;
    return root;
}

SplayNode* SplayTree::search(const float value) {
    return splay(root, value);
}

SplayNode* SplayTree::erase(const float value) {
    if (this->root == nullptr)
        return nullptr;

    this->root = splay(this->root, value);

    if (this->root->value != value)
        return this->root;

    SplayNode* temp;
    if (this->root->left == nullptr) {
        temp = this->root;
        this->root = this->root->right;
    } else {
        temp = this->root;
        this->root = splay(this->root->left, value);
        this->root->right = temp->right;
    }

    delete temp;
    return root;
}

#include <iostream>
void SplayTree::POT(const SplayNode* current) {
    if (current != nullptr) {
        std::cout << current->value << " ";
        POT(current->left);
        POT(current->right);
    }
}

void SplayTree::setRoot(SplayNode* root) {
    this->root = root;
}

SplayNode* SplayTree::getRoot() const {
    return root;
}