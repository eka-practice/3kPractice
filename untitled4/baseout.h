#ifndef BASEOUT_H
#define BASEOUT_H


#include <QObject>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QVector>

#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include <QVariant>

class Baseout:public QObject
{
    Q_OBJECT
    Q_PROPERTY(int kol)
   public:
    Q_INVOKABLE int kolAll();//колличество всех приёмников ртр и приёмников
    explicit Baseout(QObject *parent = 0);
    QVector<QString> svyaz;
    Q_INVOKABLE bool isSvyaz(int a,int b);
    Q_INVOKABLE QString vidVariant(int a);
signals:
    void sendKol(QString s);

};


#endif // BASEOUT_H
