/****************************************************************************
** Meta object code from reading C++ file 'TreeManager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../TreeManager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TreeManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN11TreeManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto TreeManager::qt_create_metaobjectdata<qt_meta_tag_ZN11TreeManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "TreeManager",
        "currentTreeTypeChanged",
        "",
        "treeUpdated",
        "nodeInserted",
        "key",
        "nodeDeleted",
        "treeCleared",
        "setTreeType",
        "type",
        "insertNode",
        "deleteNode",
        "searchNode",
        "getInorderTraversal",
        "QVariantList",
        "getPreorderTraversal",
        "getPostorderTraversal",
        "clearTree",
        "getTreeStructure",
        "updateNode",
        "oldValue",
        "occurrenceIndex",
        "newValue",
        "mode",
        "currentTreeType"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'currentTreeTypeChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'treeUpdated'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'nodeInserted'
        QtMocHelpers::SignalData<void(int)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 5 },
        }}),
        // Signal 'nodeDeleted'
        QtMocHelpers::SignalData<void(int)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 5 },
        }}),
        // Signal 'treeCleared'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'setTreeType'
        QtMocHelpers::MethodData<void(const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Method 'insertNode'
        QtMocHelpers::MethodData<void(int)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 5 },
        }}),
        // Method 'deleteNode'
        QtMocHelpers::MethodData<void(int)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 5 },
        }}),
        // Method 'searchNode'
        QtMocHelpers::MethodData<bool(int)>(12, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 5 },
        }}),
        // Method 'getInorderTraversal'
        QtMocHelpers::MethodData<QVariantList()>(13, 2, QMC::AccessPublic, 0x80000000 | 14),
        // Method 'getPreorderTraversal'
        QtMocHelpers::MethodData<QVariantList()>(15, 2, QMC::AccessPublic, 0x80000000 | 14),
        // Method 'getPostorderTraversal'
        QtMocHelpers::MethodData<QVariantList()>(16, 2, QMC::AccessPublic, 0x80000000 | 14),
        // Method 'clearTree'
        QtMocHelpers::MethodData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'getTreeStructure'
        QtMocHelpers::MethodData<QVariantList()>(18, 2, QMC::AccessPublic, 0x80000000 | 14),
        // Method 'updateNode'
        QtMocHelpers::MethodData<bool(int, int, int, const QString &)>(19, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 20 }, { QMetaType::Int, 21 }, { QMetaType::Int, 22 }, { QMetaType::QString, 23 },
        }}),
        // Method 'updateNode'
        QtMocHelpers::MethodData<bool(int, int, int)>(19, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Bool, {{
            { QMetaType::Int, 20 }, { QMetaType::Int, 21 }, { QMetaType::Int, 22 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'currentTreeType'
        QtMocHelpers::PropertyData<QString>(24, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TreeManager, qt_meta_tag_ZN11TreeManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject TreeManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11TreeManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11TreeManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11TreeManagerE_t>.metaTypes,
    nullptr
} };

void TreeManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TreeManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->currentTreeTypeChanged(); break;
        case 1: _t->treeUpdated(); break;
        case 2: _t->nodeInserted((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->nodeDeleted((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->treeCleared(); break;
        case 5: _t->setTreeType((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->insertNode((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->deleteNode((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 8: { bool _r = _t->searchNode((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { QVariantList _r = _t->getInorderTraversal();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 10: { QVariantList _r = _t->getPreorderTraversal();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 11: { QVariantList _r = _t->getPostorderTraversal();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->clearTree(); break;
        case 13: { QVariantList _r = _t->getTreeStructure();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 14: { bool _r = _t->updateNode((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 15: { bool _r = _t->updateNode((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (TreeManager::*)()>(_a, &TreeManager::currentTreeTypeChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (TreeManager::*)()>(_a, &TreeManager::treeUpdated, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (TreeManager::*)(int )>(_a, &TreeManager::nodeInserted, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (TreeManager::*)(int )>(_a, &TreeManager::nodeDeleted, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (TreeManager::*)()>(_a, &TreeManager::treeCleared, 4))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->currentTreeType(); break;
        default: break;
        }
    }
}

const QMetaObject *TreeManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TreeManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11TreeManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TreeManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void TreeManager::currentTreeTypeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TreeManager::treeUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TreeManager::nodeInserted(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void TreeManager::nodeDeleted(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void TreeManager::treeCleared()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
