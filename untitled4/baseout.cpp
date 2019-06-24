#include "baseout.h"
#include "textout.h"

Baseout::Baseout(QObject *parent)
{

}

QString Baseout::numCondition(int a)//код условия в запрошенном месте
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Data.db");
    db.open();
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT * FROM conditions");
    int i=0;
    while (query.next()){
    QString numCon = query.value(0).toString();
    if (i==a){//когда дошли до нужного номера возвращаем код
        return numCon;
    }
    i++;
    }
    db.close();
    return "i+20";//на непредвиденный случай
}

QString Baseout::timeBroken(int a)//Возвращает время поломки объекта
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Data.db");
    db.open();
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT BrokenTime FROM Devices");
    int i=0;
    while (query.next()){
        QString timeBr=query.value(0).toString();
        if (a==i)
            return timeBr;
        i++;
    }

}
