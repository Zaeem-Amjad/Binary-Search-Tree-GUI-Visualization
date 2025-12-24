#ifndef BST_H
#define BST_H

#include <vector>
#include <string>

struct BSTNode {
    int key, value;
    BSTNode* left;
    BSTNode* right;
    BSTNode* parent;
    BSTNode(int k = 0, int v = 0);
};

class BST {
public:
    BSTNode* root;

    BST();
    virtual ~BST();

    void clear(BSTNode* n);

    struct SearchResult {
        bool found;
        int depth;
        SearchResult();
        SearchResult(bool f, int d);
    };

    SearchResult search(int k);
    virtual void insert(int k, int v);
    virtual bool remove(int k);

    void transplant(BSTNode* u, BSTNode* v);
    BSTNode* minimum(BSTNode* n);

    void inorder(BSTNode* n, std::vector<int>& out);
    std::vector<int> inorderKeys();

    void preorder(BSTNode* n, std::vector<int>& out);
    std::vector<int> preorderKeys();

    void postorder(BSTNode* n, std::vector<int>& out);
    std::vector<int> postorderKeys();

    int getHeight(BSTNode* n);
    int getWidth(BSTNode* n);

    void saveToFile(const std::string& filename);
    void savePre(BSTNode* n, std::ofstream& ofs);
    void loadFromFile(const std::string& filename);
    BSTNode* loadPre(std::ifstream& ifs, BSTNode* parent);

    void clearTree();
};

#endif // BST_H