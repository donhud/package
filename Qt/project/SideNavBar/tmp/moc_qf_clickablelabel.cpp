/****************************************************************************
** Meta object code from reading C++ file 'qf_clickablelabel.h'
**
** Created: Wed Jul 1 16:19:27 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/qf_clickablelabel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qf_clickablelabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QfClickableLabel[] = {

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
      18,   17,   17,   17, 0x05,
      34,   28,   17,   17, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QfClickableLabel[] = {
    "QfClickableLabel\0\0clicked()\0label\0"
    "clicked(QfClickableLabel*)\0"
};

const QMetaObject QfClickableLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_QfClickableLabel,
      qt_meta_data_QfClickableLabel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QfClickableLabel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QfClickableLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QfClickableLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QfClickableLabel))
        return static_cast<void*>(const_cast< QfClickableLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int QfClickableLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clicked(); break;
        case 1: clicked((*reinterpret_cast< QfClickableLabel*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QfClickableLabel::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QfClickableLabel::clicked(QfClickableLabel * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
