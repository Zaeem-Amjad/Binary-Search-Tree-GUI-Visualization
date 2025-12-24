#ifndef RBTREE_H
#define RBTREE_H

#include <vector>
#include <string>

class RBNode {
public:
    int key, value;
    RBNode* left, * right, * parent;
    bool red;
    RBNode(int k = 0, int v = 0);
};

class RBTree {
public:
    RBNode* root;

    RBTree();
    ~RBTree();

    void clear(RBNode* n);

    struct SearchResult {
        bool found;
        int depth;
        SearchResult();
        SearchResult(bool f, int d);
    };

    SearchResult search(int k);

    void leftRotate(RBNode* x);
    void rightRotate(RBNode* y);

    void insert(int k, int v);
    void insertFixup(RBNode* z);

    RBNode* minimum(RBNode* n);
    void transplant(RBNode* u, RBNode* v);
    void deleteFixup(RBNode* x, RBNode* xParent);
    bool remove(int k);

    void inorder(RBNode* n, std::vector<int>& out);
    std::vector<int> inorderKeys();

    void preorder(RBNode* n, std::vector<int>& out);
    std::vector<int> preorderKeys();

    void postorder(RBNode* n, std::vector<int>& out);
    std::vector<int> postorderKeys();

    int getHeight(RBNode* n);
    int getWidth(RBNode* n);

    void saveToFile(const std::string& filename);
    void savePre(RBNode* n, std::ofstream& ofs);
    void loadFromFile(const std::string& filename);
    RBNode* loadPre(std::ifstream& ifs, RBNode* parent);

    void clearTree();
};

#endif // RBTREE_H