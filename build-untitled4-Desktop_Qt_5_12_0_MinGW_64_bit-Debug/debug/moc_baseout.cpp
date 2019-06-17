/****************************************************************************
** Meta object code from reading C++ file 'baseout.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Qt/untitled4/baseout.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'baseout.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Baseout_t {
    QByteArrayData data[10];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Baseout_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Baseout_t qt_meta_stringdata_Baseout = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Baseout"
QT_MOC_LITERAL(1, 8, 7), // "sendKol"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 1), // "s"
QT_MOC_LITERAL(4, 19, 6), // "kolAll"
QT_MOC_LITERAL(5, 26, 7), // "isSvyaz"
QT_MOC_LITERAL(6, 34, 1), // "a"
QT_MOC_LITERAL(7, 36, 1), // "b"
QT_MOC_LITERAL(8, 38, 10), // "vidVariant"
QT_MOC_LITERAL(9, 49, 3) // "kol"

    },
    "Baseout\0sendKol\0\0s\0kolAll\0isSvyaz\0a\0"
    "b\0vidVariant\0kol"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Baseout[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       1,   46, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       4,    0,   37,    2, 0x02 /* Public */,
       5,    2,   38,    2, 0x02 /* Public */,
       8,    1,   43,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // methods: parameters
    QMetaType::Int,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::QString, QMetaType::Int,    6,

 // properties: name, type, flags
       9, QMetaType::Int, 0x00095000,

       0        // eod
};

void Baseout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Baseout *_t = static_cast<Baseout *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendKol((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: { int _r = _t->kolAll();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 2: { bool _r = _t->isSvyaz((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { QString _r = _t->vidVariant((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Baseout::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Baseout::sendKol)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Baseout::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Baseout.data,
    qt_meta_data_Baseout,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Baseout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Baseout::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Baseout.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Baseout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Baseout::sendKol(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
