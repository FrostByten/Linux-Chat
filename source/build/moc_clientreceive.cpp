/****************************************************************************
** Meta object code from reading C++ file 'clientreceive.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../clientreceive.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientreceive.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ClientReceive_t {
    QByteArrayData data[7];
    char stringdata[64];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientReceive_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientReceive_t qt_meta_stringdata_ClientReceive = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ClientReceive"
QT_MOC_LITERAL(1, 14, 9), // "textAdded"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 9), // "userAdded"
QT_MOC_LITERAL(4, 35, 11), // "userRemoved"
QT_MOC_LITERAL(5, 47, 11), // "userChanged"
QT_MOC_LITERAL(6, 59, 4) // "init"

    },
    "ClientReceive\0textAdded\0\0userAdded\0"
    "userRemoved\0userChanged\0init"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientReceive[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    1,   42,    2, 0x06 /* Public */,
       4,    1,   45,    2, 0x06 /* Public */,
       5,    2,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ClientReceive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClientReceive *_t = static_cast<ClientReceive *>(_o);
        switch (_id) {
        case 0: _t->textAdded((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->userAdded((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->userRemoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->userChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->init(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ClientReceive::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientReceive::textAdded)) {
                *result = 0;
            }
        }
        {
            typedef void (ClientReceive::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientReceive::userAdded)) {
                *result = 1;
            }
        }
        {
            typedef void (ClientReceive::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientReceive::userRemoved)) {
                *result = 2;
            }
        }
        {
            typedef void (ClientReceive::*_t)(QString , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientReceive::userChanged)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject ClientReceive::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ClientReceive.data,
      qt_meta_data_ClientReceive,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ClientReceive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientReceive::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ClientReceive.stringdata))
        return static_cast<void*>(const_cast< ClientReceive*>(this));
    return QObject::qt_metacast(_clname);
}

int ClientReceive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ClientReceive::textAdded(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClientReceive::userAdded(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ClientReceive::userRemoved(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ClientReceive::userChanged(QString _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
