/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[358];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 21), // "on_RunNotepad_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 23), // "on_runThreeProc_clicked"
QT_MOC_LITERAL(4, 58, 32), // "on_pushButtonStartupInfo_clicked"
QT_MOC_LITERAL(5, 91, 25), // "on_startMyProcess_clicked"
QT_MOC_LITERAL(6, 117, 21), // "on_RunProcess_clicked"
QT_MOC_LITERAL(7, 139, 32), // "on_pushButtonSendMessage_clicked"
QT_MOC_LITERAL(8, 172, 23), // "on_lineEdit_textChanged"
QT_MOC_LITERAL(9, 196, 4), // "arg1"
QT_MOC_LITERAL(10, 201, 38), // "on_pushButtonCreateFileMappin..."
QT_MOC_LITERAL(11, 240, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(12, 262, 23), // "on_CloseMapFile_clicked"
QT_MOC_LITERAL(13, 286, 23), // "on_WriteMapFile_clicked"
QT_MOC_LITERAL(14, 310, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(15, 334, 23) // "on_textEdit_textChanged"

    },
    "MainWindow\0on_RunNotepad_clicked\0\0"
    "on_runThreeProc_clicked\0"
    "on_pushButtonStartupInfo_clicked\0"
    "on_startMyProcess_clicked\0"
    "on_RunProcess_clicked\0"
    "on_pushButtonSendMessage_clicked\0"
    "on_lineEdit_textChanged\0arg1\0"
    "on_pushButtonCreateFileMapping_clicked\0"
    "on_pushButton_clicked\0on_CloseMapFile_clicked\0"
    "on_WriteMapFile_clicked\0on_pushButton_2_clicked\0"
    "on_textEdit_textChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    1,   85,    2, 0x08 /* Private */,
      10,    0,   88,    2, 0x08 /* Private */,
      11,    0,   89,    2, 0x08 /* Private */,
      12,    0,   90,    2, 0x08 /* Private */,
      13,    0,   91,    2, 0x08 /* Private */,
      14,    0,   92,    2, 0x08 /* Private */,
      15,    0,   93,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_RunNotepad_clicked(); break;
        case 1: _t->on_runThreeProc_clicked(); break;
        case 2: _t->on_pushButtonStartupInfo_clicked(); break;
        case 3: _t->on_startMyProcess_clicked(); break;
        case 4: _t->on_RunProcess_clicked(); break;
        case 5: _t->on_pushButtonSendMessage_clicked(); break;
        case 6: _t->on_lineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_pushButtonCreateFileMapping_clicked(); break;
        case 8: _t->on_pushButton_clicked(); break;
        case 9: _t->on_CloseMapFile_clicked(); break;
        case 10: _t->on_WriteMapFile_clicked(); break;
        case 11: _t->on_pushButton_2_clicked(); break;
        case 12: _t->on_textEdit_textChanged(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
