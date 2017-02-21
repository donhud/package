/****************************************************************************
** Meta object code from reading C++ file 'customactionsdlg.h'
**
** Created: Mon Jun 29 16:29:00 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../customactionsdlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'customactionsdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_customActionsDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x0a,
      30,   20,   20,   20, 0x0a,
      40,   20,   20,   20, 0x0a,
      50,   20,   20,   20, 0x0a,
      61,   20,   20,   20, 0x0a,
      73,   20,   20,   20, 0x0a,
      97,   85,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_customActionsDialog[] = {
    "customActionsDialog\0\0accept()\0addItem()\0"
    "delItem()\0infoItem()\0readItems()\0"
    "saveItems()\0item,column\0"
    "getIcon(QTreeWidgetItem*,int)\0"
};

const QMetaObject customActionsDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_customActionsDialog,
      qt_meta_data_customActionsDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &customActionsDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *customActionsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *customActionsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_customActionsDialog))
        return static_cast<void*>(const_cast< customActionsDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int customActionsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: accept(); break;
        case 1: addItem(); break;
        case 2: delItem(); break;
        case 3: infoItem(); break;
        case 4: readItems(); break;
        case 5: saveItems(); break;
        case 6: getIcon((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
