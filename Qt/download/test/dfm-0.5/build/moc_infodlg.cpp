/****************************************************************************
** Meta object code from reading C++ file 'infodlg.h'
**
** Created: Mon Jun 29 16:28:56 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../infodlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'infodlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_propertiesDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      35,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,   17,   17,   17, 0x0a,
      63,   17,   17,   17, 0x0a,
      72,   17,   17,   17, 0x0a,
      81,   17,   17,   17, 0x0a,
      96,   17,   17,   17, 0x0a,
     116,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_propertiesDialog[] = {
    "propertiesDialog\0\0finishedSignal()\0"
    "updateSignal()\0updateInfo()\0accept()\0"
    "reject()\0finishedWork()\0checkboxesChanged()\0"
    "numericChanged(QString)\0"
};

const QMetaObject propertiesDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_propertiesDialog,
      qt_meta_data_propertiesDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &propertiesDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *propertiesDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *propertiesDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_propertiesDialog))
        return static_cast<void*>(const_cast< propertiesDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int propertiesDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: finishedSignal(); break;
        case 1: updateSignal(); break;
        case 2: updateInfo(); break;
        case 3: accept(); break;
        case 4: reject(); break;
        case 5: finishedWork(); break;
        case 6: checkboxesChanged(); break;
        case 7: numericChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void propertiesDialog::finishedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void propertiesDialog::updateSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
