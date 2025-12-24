#include "BST.h"
#include <fstream>
#include <algorithm>

BSTNode::BSTNode(int k, int v)
    : key(k), value(v), left(nullptr), right(nullptr), parent(nullptr) {
}

BST::BST() : root(nullptr) {}

BST::~BST() {
    clear(root);
}

void BST::clear(BSTNode* n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

BST::SearchResult::SearchResult()
    : found(false), depth(0) {
}

BST::SearchResult::SearchResult(bool f, int d)
    : found(f), depth(d) {
}

BST::SearchResult BST::search(int k) {
    BSTNode* n = root;
    int depth = 0;
    while (n) {
        if (n->key == k) return SearchResult(true, depth);
        n = (k < n->key) ? n->left : n->right;
        depth++;
    }
    return SearchResult(false, -1);
}

void BST::insert(int k, int v) {

    SearchResult existing = search(k);
    if (existing.found) {
        return;  // Reject duplicate
    }

    BSTNode* node = new BSTNode(k, v);
    if (!root) {
        root = node;
        return;
    }
    BSTNode* cur = root;
    BSTNode* par = nullptr;
    while (cur) {
        par = cur;

		if (k == cur->key) {
            delete node; // Clean up allocated node
            return; // Reject duplicate
        }

        cur = (k < cur->key) ? cur->left : cur->right;
    }
    node->parent = par;
    if (k < par->key)
        par->left = node;
    else
        par->right = node;
}

bool BST::remove(int k) {
    BSTNode* z = root;
    while (z && z->key != k)
        z = (k < z->key) ? z->left : z->right;
    if (!z) return false;

    if (!z->left)
        transplant(z, z->right);
    else if (!z->right)
        transplant(z, z->left);
    else {
        BSTNode* y = minimum(z->right);
        if (y->parent != z) {
            transplant(y, y->right);
            y->right = z->right;
            if (y->right) y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        if (y->left) y->left->parent = y;
    }
    delete z;
    return true;
}

void BST::transplant(BSTNode* u, BSTNode* v) {
    if (!u->parent)
        root = v;
    else if (u->parent->left == u)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v)
        v->parent = u->parent;
}

BSTNode* BST::minimum(BSTNode* n) {
    while (n && n->left)
        n = n->left;
    return n;
}

void BST::inorder(BSTNode* n, std::vector<int>& out) {
    if (!n) return;
    inorder(n->left, out);
    out.push_back(n->key);
    inorder(n->right, out);
}

std::vector<int> BST::inorderKeys() {
    std::vector<int> v;
    inorder(root, v);
    return v;
}

void BST::preorder(BSTNode* n, std::vector<int>& out) {
    if (!n) return;
    out.push_back(n->key);
    preorder(n->left, out);
    preorder(n->right, out);
}

std::vector<int> BST::preorderKeys() {
    std::vector<int> v;
    preorder(root, v);
    return v;
}

void BST::postorder(BSTNode* n, std::vector<int>& out) {
    if (!n) return;
    postorder(n->left, out);
    postorder(n->right, out);
    out.push_back(n->key);
}

std::vector<int> BST::postorderKeys() {
    std::vector<int> v;
    postorder(root, v);
    return v;
}

int BST::getHeight(BSTNode* n) {
    if (!n) return 0;
    return 1 + std::max(getHeight(n->left), getHeight(n->right));
}

int BST::getWidth(BSTNode* n) {
    if (!n) return 0;
    int h = getHeight(n);
    return (1 << h) - 1;
}

void BST::saveToFile(const std::string& filename) {
    std::ofstream ofs(filename);
    savePre(root, ofs);
}

void BST::savePre(BSTNode* n, std::ofstream& ofs) {
    if (!n) {
        ofs << "# ";
        return;
    }
    ofs << n->key << " ";
    savePre(n->left, ofs);
    savePre(n->right, ofs);
}

void BST::loadFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) return;
    clear(root);
    root = loadPre(ifs, nullptr);
}

BSTNode* BST::loadPre(std::ifstream& ifs, BSTNode* parent) {
    std::string tok;
    if (!(ifs >> tok)) return nullptr;
    if (tok == "#") return nullptr;
    int k = std::stoi(tok);
    BSTNode* n = new BSTNode(k, k);
    n->parent = parent;
    n->left = loadPre(ifs, n);
    n->right = loadPre(ifs, n);
    return n;
}

void BST::clearTree() {
    clear(root);
    root = nullptr;
}