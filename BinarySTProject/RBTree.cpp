#include "RBTree.h"
#include <fstream>
#include <algorithm>

RBNode::RBNode(int k, int v)
    : key(k), value(v), left(nullptr), right(nullptr), parent(nullptr), red(true) {
}

RBTree::RBTree() : root(nullptr) {}

RBTree::~RBTree() {
    clear(root);
}

void RBTree::clear(RBNode* n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

RBTree::SearchResult::SearchResult()
    : found(false), depth(0) {
}

RBTree::SearchResult::SearchResult(bool f, int d)
    : found(f), depth(d) {
}

RBTree::SearchResult RBTree::search(int k) {
    RBNode* cur = root;
    int depth = 0;
    while (cur) {
        if (cur->key == k) return SearchResult(true, depth);
        cur = (k < cur->key) ? cur->left : cur->right;
        depth++;
    }
    return SearchResult(false, -1);
}

void RBTree::leftRotate(RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RBTree::rightRotate(RBNode* y) {
    RBNode* x = y->left;
    y->left = x->right;
    if (x->right) x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent) root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void RBTree::insert(int k, int v) {

    SearchResult existing = search(k);
    if (existing.found) {
        return;  // Reject duplicate
    }

    RBNode* z = new RBNode(k, v);
    RBNode* y = nullptr, * x = root;
    while (x) {
        y = x;
        x = (z->key < x->key) ? x->left : x->right;
    }
    z->parent = y;
    if (!y) root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;
    z->left = z->right = nullptr;
    z->red = true;
    insertFixup(z);
}

void RBTree::insertFixup(RBNode* z) {
    while (z->parent && z->parent->red) {
        if (z->parent == z->parent->parent->left) {
            RBNode* y = z->parent->parent->right;
            if (y && y->red) {
                z->parent->red = false;
                y->red = false;
                z->parent->parent->red = true;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->red = false;
                z->parent->parent->red = true;
                rightRotate(z->parent->parent);
            }
        }
        else {
            RBNode* y = z->parent->parent->left;
            if (y && y->red) {
                z->parent->red = false;
                y->red = false;
                z->parent->parent->red = true;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->red = false;
                z->parent->parent->red = true;
                leftRotate(z->parent->parent);
            }
        }
    }
    if (root) root->red = false;
}

RBNode* RBTree::minimum(RBNode* n) {
    while (n && n->left)
        n = n->left;
    return n;
}

void RBTree::transplant(RBNode* u, RBNode* v) {
    if (!u->parent) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    if (v) v->parent = u->parent;
}

void RBTree::deleteFixup(RBNode* x, RBNode* xParent) {
    while (x != root && (!x || !x->red)) {
        if (x == xParent->left) {
            RBNode* w = xParent->right;
            if (w && w->red) {
                w->red = false;
                xParent->red = true;
                leftRotate(xParent);
                w = xParent->right;
            }
            if (w && (!w->left || !w->left->red) && (!w->right || !w->right->red)) {
                w->red = true;
                x = xParent;
                xParent = x ? x->parent : nullptr;
            }
            else if (w) {
                if (!w->right || !w->right->red) {
                    if (w->left) w->left->red = false;
                    w->red = true;
                    rightRotate(w);
                    w = xParent->right;
                }
                w->red = xParent->red;
                xParent->red = false;
                if (w->right) w->right->red = false;
                leftRotate(xParent);
                x = root;
            }
        }
        else {
            RBNode* w = xParent->left;
            if (w && w->red) {
                w->red = false;
                xParent->red = true;
                rightRotate(xParent);
                w = xParent->left;
            }
            if (w && (!w->right || !w->right->red) && (!w->left || !w->left->red)) {
                w->red = true;
                x = xParent;
                xParent = x ? x->parent : nullptr;
            }
            else if (w) {
                if (!w->left || !w->left->red) {
                    if (w->right) w->right->red = false;
                    w->red = true;
                    leftRotate(w);
                    w = xParent->left;
                }
                w->red = xParent->red;
                xParent->red = false;
                if (w->left) w->left->red = false;
                rightRotate(xParent);
                x = root;
            }
        }
    }
    if (x) x->red = false;
}

bool RBTree::remove(int k) {
    RBNode* z = root;
    while (z && z->key != k)
        z = (k < z->key) ? z->left : z->right;
    if (!z) return false;

    RBNode* y = z;
    RBNode* x;
    RBNode* xParent;
    bool yOriginalRed = y->red;

    if (!z->left) {
        x = z->right;
        xParent = z->parent;
        transplant(z, z->right);
    }
    else if (!z->right) {
        x = z->left;
        xParent = z->parent;
        transplant(z, z->left);
    }
    else {
        y = minimum(z->right);
        yOriginalRed = y->red;
        x = y->right;
        xParent = y;
        if (y->parent == z) {
            if (x) x->parent = y;
            xParent = y;
        }
        else {
            xParent = y->parent;
            transplant(y, y->right);
            y->right = z->right;
            if (y->right) y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        if (y->left) y->left->parent = y;
        y->red = z->red;
    }
    delete z;
    if (!yOriginalRed) deleteFixup(x, xParent);
    return true;
}

void RBTree::inorder(RBNode* n, std::vector<int>& out) {
    if (!n) return;
    inorder(n->left, out);
    out.push_back(n->key);
    inorder(n->right, out);
}

std::vector<int> RBTree::inorderKeys() {
    std::vector<int> v;
    inorder(root, v);
    return v;
}

void RBTree::preorder(RBNode* n, std::vector<int>& out) {
    if (!n) return;
    out.push_back(n->key);
    preorder(n->left, out);
    preorder(n->right, out);
}

std::vector<int> RBTree::preorderKeys() {
    std::vector<int> v;
    preorder(root, v);
    return v;
}

void RBTree::postorder(RBNode* n, std::vector<int>& out) {
    if (!n) return;
    postorder(n->left, out);
    postorder(n->right, out);
    out.push_back(n->key);
}

std::vector<int> RBTree::postorderKeys() {
    std::vector<int> v;
    postorder(root, v);
    return v;
}

int RBTree::getHeight(RBNode* n) {
    if (!n) return 0;
    return 1 + std::max(getHeight(n->left), getHeight(n->right));
}

int RBTree::getWidth(RBNode* n) {
    if (!n) return 0;
    int h = getHeight(n);
    return (1 << h) - 1;
}

void RBTree::saveToFile(const std::string& filename) {
    std::ofstream ofs(filename);
    savePre(root, ofs);
}

void RBTree::savePre(RBNode* n, std::ofstream& ofs) {
    if (!n) {
        ofs << "# ";
        return;
    }
    ofs << n->key << " ";
    savePre(n->left, ofs);
    savePre(n->right, ofs);
}

void RBTree::loadFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) return;
    clear(root);
    root = loadPre(ifs, nullptr);
    if (root) root->red = false;
}

RBNode* RBTree::loadPre(std::ifstream& ifs, RBNode* parent) {
    std::string tok;
    if (!(ifs >> tok)) return nullptr;
    if (tok == "#") return nullptr;
    int k = std::stoi(tok);
    RBNode* n = new RBNode(k, k);
    n->parent = parent;
    n->left = loadPre(ifs, n);
    n->right = loadPre(ifs, n);
    return n;
}

void RBTree::clearTree() {
    clear(root);
    root = nullptr;
}