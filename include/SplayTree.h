#pragma once

#include "DataStructure.h"

struct SplayNode {
    float value;
    SplayNode* left;
    SplayNode* right;
};

class SplayTree : public DataStructure{
    SplayNode* root;

    SplayNode* newSplayNode(float value);

    // Left rotation
    SplayNode* zagRot(SplayNode* x);

    // Right rotation
    SplayNode* zigRot(SplayNode* x);

    SplayNode* splay(SplayNode* root, float value);

public:
    SplayTree();

    SplayNode* insert(float value);
    SplayNode* search(float value);
    void POT(const SplayNode* current);

    void setRoot(SplayNode* root);
    [[nodiscard]] SplayNode* getRoot() const;

    ~SplayTree() = default;
};
