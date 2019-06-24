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
    explicit Baseout(QObject *parent = 0);
    QVector<QString> svyaz;
    Q_INVOKABLE QString numCondition(int a);
    Q_INVOKABLE QString timeBroken(int a);
signals:
    void sendKol(QString s);

};


#endif // BASEOUT_H
