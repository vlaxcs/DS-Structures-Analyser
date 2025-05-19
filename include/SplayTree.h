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
    SplayNode* erase(float value);
    static void POT(const SplayNode* current);

    void setRoot(SplayNode* root);
    SplayNode* getRoot() {
        return root;
    }
    [[nodiscard]] SplayNode* getRoot() const;

    ~SplayTree() override = default;
};
