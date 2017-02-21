/****************************************************************************
** Meta object code from reading C++ file 'qf_navbargroup.h'
**
** Created: Wed Jul 1 16:19:28 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/qf_navbargroup.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qf_navbargroup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QfNavBarGroup[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       2,   39, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   15,   14,   14, 0x05,
      71,   65,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     103,   96,   14,   14, 0x0a,
     121,  116,   14,   14, 0x08,
     157,   14,   14,   14, 0x08,

 // properties: name, type, flags
     182,  174, 0x0a095103,
     193,  188, 0x01095003,

       0        // eod
};

static const char qt_meta_stringdata_QfNavBarGroup[] = {
    "QfNavBarGroup\0\0group,item\0"
    "selected(QfNavBarGroup*,QfNavBarItem*)\0"
    "group\0expanded(QfNavBarGroup*)\0expand\0"
    "expand(bool)\0item\0onItemSelected(QfSelectableWidget*)\0"
    "onTitleClicked()\0QString\0title\0bool\0"
    "isExpanded\0"
};

const QMetaObject QfNavBarGroup::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QfNavBarGroup,
      qt_meta_data_QfNavBarGroup, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QfNavBarGroup::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QfNavBarGroup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QfNavBarGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QfNavBarGroup))
        return static_cast<void*>(const_cast< QfNavBarGroup*>(this));
    return QWidget::qt_metacast(_clname);
}

int QfNavBarGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: selected((*reinterpret_cast< QfNavBarGroup*(*)>(_a[1])),(*reinterpret_cast< QfNavBarItem*(*)>(_a[2]))); break;
        case 1: expanded((*reinterpret_cast< QfNavBarGroup*(*)>(_a[1]))); break;
        case 2: expand((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: onItemSelected((*reinterpret_cast< QfSelectableWidget*(*)>(_a[1]))); break;
        case 4: onTitleClicked(); break;
        default: ;
        }
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = title(); break;
        case 1: *reinterpret_cast< bool*>(_v) = isExpanded(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setTitle(*reinterpret_cast< QString*>(_v)); break;
        case 1: expand(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QfNavBarGroup::selected(QfNavBarGroup * _t1, QfNavBarItem * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QfNavBarGroup::expanded(QfNavBarGroup * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
