#ifndef TREEMANAGER_H
#define TREEMANAGER_H

#include <QObject>
#include <QVariantList>
#include <QVariantMap>
#include <QString>
#include "BST.h"
#include "AVL.h"
#include "RBTree.h"

class TreeManager : public QObject
{
    Q_OBJECT
        Q_PROPERTY(QString currentTreeType READ currentTreeType NOTIFY currentTreeTypeChanged)

public:
    explicit TreeManager(QObject* parent = nullptr);
    ~TreeManager();

    QString currentTreeType() const { return m_currentTreeType; }

    Q_INVOKABLE void setTreeType(const QString& type);
    Q_INVOKABLE void insertNode(int key);
    Q_INVOKABLE void deleteNode(int key);
    Q_INVOKABLE bool searchNode(int key);
    Q_INVOKABLE QVariantList getInorderTraversal();
    Q_INVOKABLE QVariantList getPreorderTraversal();
    Q_INVOKABLE QVariantList getPostorderTraversal();
    Q_INVOKABLE void clearTree();
    Q_INVOKABLE QVariantList getTreeStructure();
    Q_INVOKABLE bool updateNode(int oldValue, int occurrenceIndex, int newValue, const QString& mode = "any");

signals:
    void currentTreeTypeChanged();
    void treeUpdated();
    void nodeInserted(int key);
    void nodeDeleted(int key);
    void treeCleared();

private:
    BST* m_bst;
    AVL* m_avl;
    RBTree* m_rbTree;
    QString m_currentTreeType;

    void buildTreeStructure(BSTNode* node, QVariantList& list, int level, double x, double xOffset);
    void buildRBTreeStructure(RBNode* node, QVariantList& list, int level, double x, double xOffset);

    void saveToFile(const QString& filename);
    void loadFromFile(const QString& filename);
};

#endif // TREEMANAGER_H