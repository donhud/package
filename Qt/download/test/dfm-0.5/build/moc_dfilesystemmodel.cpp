/****************************************************************************
** Meta object code from reading C++ file 'dfilesystemmodel.h'
**
** Created: Mon Jun 29 16:29:09 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dfilesystemmodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dfilesystemmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DFileSystemModel[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      39,   18,   17,   17, 0x05,
      97,   91,   17,   17, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_DFileSystemModel[] = {
    "DFileSystemModel\0\0data,newPath,cutList\0"
    "dragDropPaste(const QMimeData*,QString,QStringList)\0"
    "index\0thumbUpdate(QModelIndex)\0"
};

const QMetaObject DFileSystemModel::staticMetaObject = {
    { &QFileSystemModel::staticMetaObject, qt_meta_stringdata_DFileSystemModel,
      qt_meta_data_DFileSystemModel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DFileSystemModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DFileSystemModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DFileSystemModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DFileSystemModel))
        return static_cast<void*>(const_cast< DFileSystemModel*>(this));
    return QFileSystemModel::qt_metacast(_clname);
}

int DFileSystemModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFileSystemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: dragDropPaste((*reinterpret_cast< const QMimeData*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QStringList(*)>(_a[3]))); break;
        case 1: thumbUpdate((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void DFileSystemModel::dragDropPaste(const QMimeData * _t1, QString _t2, QStringList _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DFileSystemModel::thumbUpdate(const QModelIndex _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
