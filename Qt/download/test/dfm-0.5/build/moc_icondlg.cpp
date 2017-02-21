/****************************************************************************
** Meta object code from reading C++ file 'icondlg.h'
**
** Created: Mon Jun 29 16:28:57 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../icondlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'icondlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_icondlg[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      21,    8,    8,    8, 0x0a,
      33,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_icondlg[] = {
    "icondlg\0\0scanTheme()\0loadIcons()\0"
    "accept()\0"
};

const QMetaObject icondlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_icondlg,
      qt_meta_data_icondlg, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &icondlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *icondlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *icondlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_icondlg))
        return static_cast<void*>(const_cast< icondlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int icondlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: scanTheme(); break;
        case 1: loadIcons(); break;
        case 2: accept(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
