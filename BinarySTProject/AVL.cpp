#include "AVL.h"
#include <algorithm>

int AVL::height(BSTNode* n) {
    if (!n) return 0;
    return 1 + std::max(height(n->left), height(n->right));
}

int AVL::balanceFactor(BSTNode* n) {
    return height(n->left) - height(n->right);
}

BSTNode* AVL::rightRotate(BSTNode* y) {
    BSTNode* x = y->left;
    BSTNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    x->parent = y->parent;
    y->parent = x;
    if (T2) T2->parent = y;

    if (!x->parent)
        root = x;
    else if (x->parent->left == y)
        x->parent->left = x;
    else
        x->parent->right = x;

    return x;
}

BSTNode* AVL::leftRotate(BSTNode* x) {
    BSTNode* y = x->right;
    BSTNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    y->parent = x->parent;
    x->parent = y;
    if (T2) T2->parent = x;

    if (!y->parent)
        root = y;
    else if (y->parent->left == x)
        y->parent->left = y;
    else
        y->parent->right = y;

    return y;
}

BSTNode* AVL::rebalance(BSTNode* node) {
    int bf = balanceFactor(node);
    if (bf > 1) {
        if (balanceFactor(node->left) >= 0)
            return rightRotate(node);
        else {
            leftRotate(node->left);
            return rightRotate(node);
        }
    }
    else if (bf < -1) {
        if (balanceFactor(node->right) <= 0)
            return leftRotate(node);
        else {
            rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

BSTNode* AVL::insertRec(BSTNode* node, int k, int v, BSTNode* parent) {
    if (!node) {
        BSTNode* n = new BSTNode(k, v);
        n->parent = parent;
        return n;
    }
    if (k < node->key)
        node->left = insertRec(node->left, k, v, node);
    else
        node->right = insertRec(node->right, k, v, node);
    return rebalance(node);
}

void AVL::insert(int k, int v) {

    SearchResult existing = search(k);
    if (existing.found) {
        return;  // Reject duplicate
    }

    root = insertRec(root, k, v, nullptr);
    if (root) root->parent = nullptr;
}

std::pair<BSTNode*, bool> AVL::removeRec(BSTNode* node, int k) {
    if (!node) return {nullptr, false};
    bool removed = false;
    if (k < node->key) {
        auto res = removeRec(node->left, k);
        node->left = res.first;
        removed = res.second;
        if (node->left) node->left->parent = node;
    }
    else if (k > node->key) {
        auto res = removeRec(node->right, k);
        node->right = res.first;
        removed = res.second;
        if (node->right) node->right->parent = node;
    }
    else {
        removed = true;
        if (!node->left || !node->right) {
            BSTNode* tmp = node->left ? node->left : node->right;
            if (!tmp) {
                delete node;
                return {nullptr, true};
            }
            else {
                tmp->parent = node->parent;
                delete node;
                return {tmp, true};
            }
        }
        else {
            BSTNode* succ = minimum(node->right);
            node->key = succ->key;
            node->value = succ->value;
            auto res = removeRec(node->right, succ->key);
            node->right = res.first;
            // If right child exists, fix parent pointer
            if (node->right) node->right->parent = node;
            removed = res.second || removed;
        }
    }
    // Only rebalance if node still exists
    if (!node) return {nullptr, removed};
    BSTNode* balanced = rebalance(node);
    return {balanced, removed};
}

bool AVL::remove(int k) {
    auto res = removeRec(root, k);
    root = res.first;
    if (root) root->parent = nullptr;
    return res.second;
}