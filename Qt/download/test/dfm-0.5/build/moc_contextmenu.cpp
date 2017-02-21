/****************************************************************************
** Meta object code from reading C++ file 'contextmenu.h'
**
** Created: Mon Jun 29 16:28:55 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../contextmenu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'contextmenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_contextmenu[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      33,   12,   12,   12, 0x05,
      49,   12,   12,   12, 0x05,
      68,   12,   12,   12, 0x05,
      84,   12,   12,   12, 0x05,
      99,   12,   12,   12, 0x05,
     116,   12,   12,   12, 0x05,
     134,   12,   12,   12, 0x05,
     152,   12,   12,   12, 0x05,
     176,   12,   12,   12, 0x05,
     198,   12,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_contextmenu[] = {
    "contextmenu\0\0execFileTriggered()\0"
    "openTriggered()\0openTabTriggered()\0"
    "copyTriggered()\0cutTriggered()\0"
    "pasteTriggered()\0deleteTriggered()\0"
    "renameTriggered()\0createFolderTriggered()\0"
    "createFileTriggered()\0infoFileTriggered()\0"
};

const QMetaObject contextmenu::staticMetaObject = {
    { &QMenu::staticMetaObject, qt_meta_stringdata_contextmenu,
      qt_meta_data_contextmenu, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &contextmenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *contextmenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *contextmenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_contextmenu))
        return static_cast<void*>(const_cast< contextmenu*>(this));
    return QMenu::qt_metacast(_clname);
}

int contextmenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: execFileTriggered(); break;
        case 1: openTriggered(); break;
        case 2: openTabTriggered(); break;
        case 3: copyTriggered(); break;
        case 4: cutTriggered(); break;
        case 5: pasteTriggered(); break;
        case 6: deleteTriggered(); break;
        case 7: renameTriggered(); break;
        case 8: createFolderTriggered(); break;
        case 9: createFileTriggered(); break;
        case 10: infoFileTriggered(); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void contextmenu::execFileTriggered()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void contextmenu::openTriggered()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void contextmenu::openTabTriggered()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void contextmenu::copyTriggered()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void contextmenu::cutTriggered()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void contextmenu::pasteTriggered()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void contextmenu::deleteTriggered()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void contextmenu::renameTriggered()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void contextmenu::createFolderTriggered()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void contextmenu::createFileTriggered()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}

// SIGNAL 10
void contextmenu::infoFileTriggered()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}
QT_END_MOC_NAMESPACE
