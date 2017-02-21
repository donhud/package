/****************************************************************************
** Meta object code from reading C++ file 'texteditor.h'
**
** Created: Mon Jun 29 16:28:59 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../texteditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'texteditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TextEditor[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      22,   11,   11,   11, 0x08,
      34,   11,   29,   11, 0x08,
      41,   11,   29,   11, 0x08,
      50,   11,   11,   11, 0x08,
      72,   11,   11,   11, 0x08,
      85,   11,   11,   11, 0x08,
      96,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TextEditor[] = {
    "TextEditor\0\0newFile()\0open()\0bool\0"
    "save()\0saveAs()\0documentWasModified()\0"
    "hl_toogled()\0findText()\0clrresults()\0"
};

const QMetaObject TextEditor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_TextEditor,
      qt_meta_data_TextEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TextEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TextEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TextEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TextEditor))
        return static_cast<void*>(const_cast< TextEditor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int TextEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newFile(); break;
        case 1: open(); break;
        case 2: { bool _r = save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = saveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: documentWasModified(); break;
        case 5: hl_toogled(); break;
        case 6: findText(); break;
        case 7: clrresults(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
