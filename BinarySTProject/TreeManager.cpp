#include "TreeManager.h"
#include <QFile>
#include <QTextStream>
#include <cmath>

TreeManager::TreeManager(QObject* parent)
    : QObject(parent)
    , m_bst(new BST())
    , m_avl(new AVL())
    , m_rbTree(new RBTree())
    , m_currentTreeType("BST")
{
    // Load existing trees from files
    loadFromFile("bst.txt");
    loadFromFile("avl.txt");
    loadFromFile("rb.txt");
}

TreeManager::~TreeManager()
{
    delete m_bst;
    delete m_avl;
    delete m_rbTree;
}

void TreeManager::setTreeType(const QString& type)
{
    if (m_currentTreeType != type) {
        m_currentTreeType = type;
        emit currentTreeTypeChanged();
        emit treeUpdated();
    }
}

void TreeManager::insertNode(int key)
{
    if (m_currentTreeType == "BST") {
        m_bst->insert(key, key);
        saveToFile("bst.txt");
    }
    else if (m_currentTreeType == "AVL") {
        m_avl->insert(key, key);
        saveToFile("avl.txt");
    }
    else if (m_currentTreeType == "RB") {
        m_rbTree->insert(key, key);
        saveToFile("rb.txt");
    }

    emit nodeInserted(key);
    emit treeUpdated();
}

void TreeManager::deleteNode(int key)
{
    if (m_currentTreeType == "BST") {
        m_bst->remove(key);
        saveToFile("bst.txt");
    }
    else if (m_currentTreeType == "AVL") {
        m_avl->remove(key);
        saveToFile("avl.txt");
    }
    else if (m_currentTreeType == "RB") {
        m_rbTree->remove(key);
        saveToFile("rb.txt");
    }

    emit nodeDeleted(key);
    emit treeUpdated();
}

bool TreeManager::searchNode(int key)
{
    BST::SearchResult result;

    if (m_currentTreeType == "BST") {
        result = m_bst->search(key);
    }
    else if (m_currentTreeType == "AVL") {
        result = m_avl->search(key);
    }
    else if (m_currentTreeType == "RB") {
        auto rbResult = m_rbTree->search(key);
        result.found = rbResult.found;
        result.depth = rbResult.depth;
    }

    return result.found;
}

QVariantList TreeManager::getInorderTraversal()
{
    QVariantList result;
    std::vector<int> keys;

    if (m_currentTreeType == "BST") {
        keys = m_bst->inorderKeys();
    }
    else if (m_currentTreeType == "AVL") {
        keys = m_avl->inorderKeys();
    }
    else if (m_currentTreeType == "RB") {
        keys = m_rbTree->inorderKeys();
    }

    for (int key : keys) {
        result.append(key);
    }

    return result;
}

QVariantList TreeManager::getPreorderTraversal()
{
    QVariantList result;
    std::vector<int> keys;

    if (m_currentTreeType == "BST") {
        keys = m_bst->preorderKeys();
    }
    else if (m_currentTreeType == "AVL") {
        keys = m_avl->preorderKeys();
    }
    else if (m_currentTreeType == "RB") {
        keys = m_rbTree->preorderKeys();
    }

    for (int key : keys) {
        result.append(key);
    }

    return result;
}

QVariantList TreeManager::getPostorderTraversal()
{
    QVariantList result;
    std::vector<int> keys;

    if (m_currentTreeType == "BST") {
        keys = m_bst->postorderKeys();
    }
    else if (m_currentTreeType == "AVL") {
        keys = m_avl->postorderKeys();
    }
    else if (m_currentTreeType == "RB") {
        keys = m_rbTree->postorderKeys();
    }

    for (int key : keys) {
        result.append(key);
    }

    return result;
}

void TreeManager::clearTree()
{
    if (m_currentTreeType == "BST") {
        m_bst->clearTree();
        saveToFile("bst.txt");
    }
    else if (m_currentTreeType == "AVL") {
        m_avl->clearTree();
        saveToFile("avl.txt");
    }
    else if (m_currentTreeType == "RB") {
        m_rbTree->clearTree();
        saveToFile("rb.txt");
    }

    emit treeCleared();
    emit treeUpdated();
}

// Helper to update value within vector of keys for BST/AVL/RB
static bool updateInVector(std::vector<int>& keys, int oldValue, int occurrenceIndex, int newValue, const QString& mode)
{
    if (mode == "beginning") {
        if (!keys.empty()) { keys.front() = newValue; return true; }
        return false;
    }
    else if (mode == "end") {
        if (!keys.empty()) { keys.back() = newValue; return true; }
        return false;
    }
    else { // any with occurrenceIndex (1-based)
        int count = 0;
        for (size_t i = 0; i < keys.size(); ++i) {
            if (keys[i] == oldValue) {
                ++count;
                if (count == occurrenceIndex) { keys[i] = newValue; return true; }
            }
        }
        return false;
    }
}

// Implementation of updateNode declared in header
bool TreeManager::updateNode(int oldValue, int occurrenceIndex, int newValue, const QString& mode)
{
    // Approach: Rebuild tree from traversal keys with updated value.
    if (m_currentTreeType == "BST") {
        auto keys = m_bst->inorderKeys();
        bool ok = updateInVector(keys, oldValue, occurrenceIndex, newValue, mode);
        if (!ok) return false;
        m_bst->clearTree();
        for (int k : keys) m_bst->insert(k, k);
        saveToFile("bst.txt");
        emit treeUpdated();
        return true;
    }
    else if (m_currentTreeType == "AVL") {
        auto keys = m_avl->inorderKeys();
        bool ok = updateInVector(keys, oldValue, occurrenceIndex, newValue, mode);
        if (!ok) return false;
        m_avl->clearTree();
        for (int k : keys) m_avl->insert(k, k);
        saveToFile("avl.txt");
        emit treeUpdated();
        return true;
    }
    else if (m_currentTreeType == "RB") {
        auto keys = m_rbTree->inorderKeys();
        bool ok = updateInVector(keys, oldValue, occurrenceIndex, newValue, mode);
        if (!ok) return false;
        m_rbTree->clearTree();
        for (int k : keys) m_rbTree->insert(k, k);
        saveToFile("rb.txt");
        emit treeUpdated();
        return true;
    }
    return false;
}

void TreeManager::buildTreeStructure(BSTNode* node, QVariantList& list, int level, double x, double xOffset)
{
    if (!node) return;

    QVariantMap nodeData;
    nodeData["key"] = node->key;
    nodeData["level"] = level;
    nodeData["x"] = x;
    nodeData["color"] = "blue";
    nodeData["parent"] = node->parent ? node->parent->key : -1;

    list.append(nodeData);

    double newOffset = xOffset * 0.5;
    if (node->left) {
        buildTreeStructure(node->left, list, level + 1, x - xOffset, newOffset);
    }
    if (node->right) {
        buildTreeStructure(node->right, list, level + 1, x + xOffset, newOffset);
    }
}

void TreeManager::buildRBTreeStructure(RBNode* node, QVariantList& list, int level, double x, double xOffset)
{
    if (!node) return;

    QVariantMap nodeData;
    nodeData["key"] = node->key;
    nodeData["level"] = level;
    nodeData["x"] = x;
    nodeData["color"] = node->red ? "red" : "black";
    nodeData["parent"] = node->parent ? node->parent->key : -1;

    list.append(nodeData);

    double newOffset = xOffset * 0.5;
    if (node->left) {
        buildRBTreeStructure(node->left, list, level + 1, x - xOffset, newOffset);
    }
    if (node->right) {
        buildRBTreeStructure(node->right, list, level + 1, x + xOffset, newOffset);
    }
}

QVariantList TreeManager::getTreeStructure()
{
    QVariantList result;

    if (m_currentTreeType == "BST") {
        if (m_bst->root) {
            int treeHeight = m_bst->getHeight(m_bst->root);
            double initialOffset = std::pow(2, treeHeight - 1) * 50;
            buildTreeStructure(m_bst->root, result, 0, 400, initialOffset);
        }
    }
    else if (m_currentTreeType == "AVL") {
        if (m_avl->root) {
            int treeHeight = m_avl->getHeight(m_avl->root);
            double initialOffset = std::pow(2, treeHeight - 1) * 50;
            buildTreeStructure(m_avl->root, result, 0, 400, initialOffset);
        }
    }
    else if (m_currentTreeType == "RB") {
        if (m_rbTree->root) {
            int treeHeight = m_rbTree->getHeight(m_rbTree->root);
            double initialOffset = std::pow(2, treeHeight - 1) * 50;
            buildRBTreeStructure(m_rbTree->root, result, 0, 400, initialOffset);
        }
    }

    return result;
}

void TreeManager::saveToFile(const QString& filename)
{
    if (m_currentTreeType == "BST") {
        m_bst->saveToFile(filename.toStdString());
    }
    else if (m_currentTreeType == "AVL") {
        m_avl->saveToFile(filename.toStdString());
    }
    else if (m_currentTreeType == "RB") {
        m_rbTree->saveToFile(filename.toStdString());
    }
}

void TreeManager::loadFromFile(const QString& filename)
{
    QFile file(filename);
    if (!file.exists()) return;

    if (filename.contains("bst")) {
        m_bst->loadFromFile(filename.toStdString());
    }
    else if (filename.contains("avl")) {
        m_avl->loadFromFile(filename.toStdString());
    }
    else if (filename.contains("rb")) {
        m_rbTree->loadFromFile(filename.toStdString());
    }
}