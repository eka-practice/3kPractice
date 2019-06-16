/****************************************************************************
** Meta object code from reading C++ file 'textout.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Qt/untitled4/textout.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'textout.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TextOut_t {
    QByteArrayData data[24];
    char stringdata0[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TextOut_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TextOut_t qt_meta_stringdata_TextOut = {
    {
QT_MOC_LITERAL(0, 0, 7), // "TextOut"
QT_MOC_LITERAL(1, 8, 19), // "somePropertyChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 15), // "someMaxRChanged"
QT_MOC_LITERAL(4, 45, 12), // "perehodPoisk"
QT_MOC_LITERAL(5, 58, 1), // "a"
QT_MOC_LITERAL(6, 60, 7), // "nowTime"
QT_MOC_LITERAL(7, 68, 7), // "dalSvaz"
QT_MOC_LITERAL(8, 76, 1), // "b"
QT_MOC_LITERAL(9, 78, 9), // "sendColor"
QT_MOC_LITERAL(10, 88, 8), // "getColor"
QT_MOC_LITERAL(11, 97, 1), // "s"
QT_MOC_LITERAL(12, 99, 8), // "readFile"
QT_MOC_LITERAL(13, 108, 1), // "t"
QT_MOC_LITERAL(14, 110, 6), // "isSvaz"
QT_MOC_LITERAL(15, 117, 10), // "rasprRange"
QT_MOC_LITERAL(16, 128, 11), // "maxKolRange"
QT_MOC_LITERAL(17, 140, 6), // "kolAll"
QT_MOC_LITERAL(18, 147, 10), // "vidVariant"
QT_MOC_LITERAL(19, 158, 13), // "timeCondition"
QT_MOC_LITERAL(20, 172, 6), // "kolCon"
QT_MOC_LITERAL(21, 179, 10), // "maxConTime"
QT_MOC_LITERAL(22, 190, 3), // "kol"
QT_MOC_LITERAL(23, 194, 4) // "maxR"

    },
    "TextOut\0somePropertyChanged\0\0"
    "someMaxRChanged\0perehodPoisk\0a\0nowTime\0"
    "dalSvaz\0b\0sendColor\0getColor\0s\0readFile\0"
    "t\0isSvaz\0rasprRange\0maxKolRange\0kolAll\0"
    "vidVariant\0timeCondition\0kolCon\0"
    "maxConTime\0kol\0maxR"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TextOut[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       2,  132, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,
       3,    0,   90,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       4,    2,   91,    2, 0x02 /* Public */,
       7,    2,   96,    2, 0x02 /* Public */,
       9,    2,  101,    2, 0x02 /* Public */,
      10,    3,  106,    2, 0x02 /* Public */,
      12,    1,  113,    2, 0x02 /* Public */,
      14,    2,  116,    2, 0x02 /* Public */,
      15,    0,  121,    2, 0x02 /* Public */,
      16,    0,  122,    2, 0x02 /* Public */,
      17,    0,  123,    2, 0x02 /* Public */,
      18,    1,  124,    2, 0x02 /* Public */,
      19,    1,  127,    2, 0x02 /* Public */,
      20,    0,  130,    2, 0x02 /* Public */,
      21,    0,  131,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,    5,    8,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,    5,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,    5,    8,   11,
    QMetaType::QString, QMetaType::Int,   13,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,    5,    8,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,    5,
    QMetaType::Int, QMetaType::Int,    5,
    QMetaType::Int,
    QMetaType::Int,

 // properties: name, type, flags
      22, QMetaType::Int, 0x00495003,
      23, QMetaType::Int, 0x00495003,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void TextOut::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TextOut *_t = static_cast<TextOut *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->somePropertyChanged(); break;
        case 1: _t->someMaxRChanged(); break;
        case 2: _t->perehodPoisk((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: { bool _r = _t->dalSvaz((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { QString _r = _t->sendColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->getColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 6: { QString _r = _t->readFile((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->isSvaz((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { QString _r = _t->rasprRange();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 9: { int _r = _t->maxKolRange();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 10: { int _r = _t->kolAll();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 11: { QString _r = _t->vidVariant((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 12: { int _r = _t->timeCondition((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 13: { int _r = _t->kolCon();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 14: { int _r = _t->maxConTime();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TextOut::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TextOut::somePropertyChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TextOut::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TextOut::someMaxRChanged)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        TextOut *_t = static_cast<TextOut *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->getSomeProperty(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->getMaxRProperty(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        TextOut *_t = static_cast<TextOut *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setSomeProperty(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setMaxRProperty(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject TextOut::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_TextOut.data,
    qt_meta_data_TextOut,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TextOut::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TextOut::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TextOut.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TextOut::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void TextOut::somePropertyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TextOut::someMaxRChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
