/****************************************************************************
** Meta object code from reading C++ file 'dispwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/MediaManager/dispwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dispwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_dispwidget_t {
    QByteArrayData data[12];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_dispwidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_dispwidget_t qt_meta_stringdata_dispwidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "dispwidget"
QT_MOC_LITERAL(1, 11, 14), // "displayStopped"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 14), // "displayStarted"
QT_MOC_LITERAL(4, 42, 12), // "errorMessage"
QT_MOC_LITERAL(5, 55, 5), // "error"
QT_MOC_LITERAL(6, 61, 12), // "updateScreen"
QT_MOC_LITERAL(7, 74, 5), // "image"
QT_MOC_LITERAL(8, 80, 20), // "endOfInputFromPlayer"
QT_MOC_LITERAL(9, 101, 15), // "mousePressEvent"
QT_MOC_LITERAL(10, 117, 12), // "QMouseEvent*"
QT_MOC_LITERAL(11, 130, 5) // "event"

    },
    "dispwidget\0displayStopped\0\0displayStarted\0"
    "errorMessage\0error\0updateScreen\0image\0"
    "endOfInputFromPlayer\0mousePressEvent\0"
    "QMouseEvent*\0event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dispwidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    1,   46,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   49,    2, 0x0a /* Public */,
       8,    0,   52,    2, 0x0a /* Public */,
       9,    1,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QImage,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,

       0        // eod
};

void dispwidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<dispwidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->displayStopped(); break;
        case 1: _t->displayStarted(); break;
        case 2: _t->errorMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->updateScreen((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 4: _t->endOfInputFromPlayer(); break;
        case 5: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (dispwidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dispwidget::displayStopped)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (dispwidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dispwidget::displayStarted)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (dispwidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dispwidget::errorMessage)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject dispwidget::staticMetaObject = { {
    &QLabel::staticMetaObject,
    qt_meta_stringdata_dispwidget.data,
    qt_meta_data_dispwidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *dispwidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dispwidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_dispwidget.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int dispwidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void dispwidget::displayStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void dispwidget::displayStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void dispwidget::errorMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
