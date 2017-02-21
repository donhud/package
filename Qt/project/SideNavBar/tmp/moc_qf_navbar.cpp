/****************************************************************************
** Meta object code from reading C++ file 'qf_navbar.h'
**
** Created: Wed Jul 1 16:19:27 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/qf_navbar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qf_navbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QfNavBar[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       2,   24, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   10,    9,    9, 0x08,
      59,   48,    9,    9, 0x08,

 // properties: name, type, flags
     111,  104, 0x43095103,
     126,  104, 0x43095103,

       0        // eod
};

static const char qt_meta_stringdata_QfNavBar[] = {
    "QfNavBar\0\0group\0onGroupExpanded(QfNavBarGroup*)\0"
    "group,item\0onItemSelected(QfNavBarGroup*,QfNavBarItem*)\0"
    "QColor\0selectionColor\0backgroundColor\0"
};

const QMetaObject QfNavBar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QfNavBar,
      qt_meta_data_QfNavBar, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QfNavBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QfNavBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QfNavBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QfNavBar))
        return static_cast<void*>(const_cast< QfNavBar*>(this));
    return QWidget::qt_metacast(_clname);
}

int QfNavBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onGroupExpanded((*reinterpret_cast< QfNavBarGroup*(*)>(_a[1]))); break;
        case 1: onItemSelected((*reinterpret_cast< QfNavBarGroup*(*)>(_a[1])),(*reinterpret_cast< QfNavBarItem*(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = selectionColor(); break;
        case 1: *reinterpret_cast< QColor*>(_v) = backgroundColor(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setSelectionColor(*reinterpret_cast< QColor*>(_v)); break;
        case 1: setBackgroundColor(*reinterpret_cast< QColor*>(_v)); break;
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
QT_END_MOC_NAMESPACE
