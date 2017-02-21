/****************************************************************************
** Meta object code from reading C++ file 'Hmainwindow.h'
**
** Created: Mon Jun 29 16:29:04 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../hexedit/Hmainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Hmainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HMainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      20,   12,   12,   12, 0x08,
      38,   12,   12,   12, 0x08,
      54,   12,   49,   12, 0x08,
      61,   12,   49,   12, 0x08,
      70,   12,   12,   12, 0x08,
     100,   12,   12,   12, 0x08,
     129,  121,   12,   12, 0x08,
     150,  145,   12,   12, 0x08,
     178,  173,   12,   12, 0x08,
     191,   12,   12,   12, 0x08,
     211,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_HMainWindow[] = {
    "HMainWindow\0\0open()\0optionsAccepted()\0"
    "findNext()\0bool\0save()\0saveAs()\0"
    "saveSelectionToReadableFile()\0"
    "saveToReadableFile()\0address\0"
    "setAddress(int)\0mode\0setOverwriteMode(bool)\0"
    "size\0setSize(int)\0showOptionsDialog()\0"
    "showSearchDialog()\0"
};

const QMetaObject HMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_HMainWindow,
      qt_meta_data_HMainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HMainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HMainWindow))
        return static_cast<void*>(const_cast< HMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int HMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: open(); break;
        case 1: optionsAccepted(); break;
        case 2: findNext(); break;
        case 3: { bool _r = save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = saveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: saveSelectionToReadableFile(); break;
        case 6: saveToReadableFile(); break;
        case 7: setAddress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: setOverwriteMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: setSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: showOptionsDialog(); break;
        case 11: showSearchDialog(); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
