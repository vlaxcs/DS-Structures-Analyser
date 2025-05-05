#pragma once

#include <iostream>

struct SplayNode {
    float value;
    SplayNode* left;
    SplayNode* right;
};

class SplayTree {
    SplayNode* root;

    SplayNode* newSplayNode(float value);

    // Left rotation
    SplayNode* zagRot(SplayNode* x);

    // Right rotation
    SplayNode* zigRot(SplayNode* x);

    SplayNode* splay(SplayNode* root, float value);

public:
    SplayTree();

    SplayNode* insert(int key);
    void POT(SplayNode* current);

    void setRoot(SplayNode* root);
    [[nodiscard]] SplayNode* getRoot() const;

};
