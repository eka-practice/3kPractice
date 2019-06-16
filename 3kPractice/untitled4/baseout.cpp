#include "baseout.h"
#include "textout.h"



int Baseout::kolAll()
{
    return 1;
}

Baseout::Baseout(QObject *parent)
{
//    QSqlDatabase db;
//    db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("D:\\Qt\\BasaSQ.db");
//    db.open();
//    //Осуществляем запрос
//    QSqlQuery query;
//    query.exec("SELECT * FROM RTR");
//    while (query.next()){
//        QString radio = query.value(2).toString(),str="",num=query.value(0).toString();
//        for (int i = 0; i < radio.length(); ++i) {

//            if (radio[i]!=','){
//                str+=radio[i];
//            } else if(radio[i]==','){
//                svyaz.append(num+'|'+str);
//                str="";
//            }
//        }
//        svyaz.append(num+'|'+str);

//    }
//    TextOut *wr;
//    wr = new TextOut(this);
//    QObject::connect(this,SIGNAL(sendKol(QString)),wr,SLOT(getKol(QString)));
//    for (int i = 0; i < svyaz.size(); ++i) {
//        emit sendKol(svyaz[i]);
//    }

//    qDebug()<<svyaz.size();
//    db.close();
}

bool Baseout::isSvyaz(int a, int b)//проверка имеется ли связь между запрошенными объектами
{
//        QString str1=QString::number(a+1)+'|'+QString::number(b+1);
//        for (int i=0;i<svyaz.size();i++){
//            if (str1==svyaz[i]){
//                return true;
//            }
//        }
        return false;

}

QString Baseout::vidVariant(int a)
{
        QSqlDatabase db;
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("D:\\Qt\\BasaSQ.db");
        db.open();
        //Осуществляем запрос
        QSqlQuery query;
        query.exec("SELECT Vid FROM Object");
        //qDebug()<<vid+".png";
        db.close();
        return /*vid+*/"1.png";
}
