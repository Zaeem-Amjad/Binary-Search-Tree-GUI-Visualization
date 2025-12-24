#ifndef AVL_H
#define AVL_H

#include "BST.h"
#include <utility>

class AVL : public BST {
public:
    int height(BSTNode* n);
    int balanceFactor(BSTNode* n);

    BSTNode* rightRotate(BSTNode* y);
    BSTNode* leftRotate(BSTNode* x);
    BSTNode* rebalance(BSTNode* node);

    BSTNode* insertRec(BSTNode* node, int k, int v, BSTNode* parent);
    void insert(int k, int v) override;

    std::pair<BSTNode*, bool> removeRec(BSTNode* node, int k);
    bool remove(int k) override;
};

#endif // AVL_H