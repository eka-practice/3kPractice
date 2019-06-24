#ifndef TEXTOUT_H
#define TEXTOUT_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QVector>

#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include <QVariant>

class TextOut:public QObject
{
    Q_OBJECT
    Q_PROPERTY(int kol READ getSomeProperty WRITE setSomeProperty NOTIFY somePropertyChanged)
    Q_PROPERTY(int maxR READ getMaxRProperty WRITE setMaxRProperty NOTIFY someMaxRChanged)
public:
    QVector<QString> nomerVarianta;//хранит номер варианта считанный из БД
    QVector<QString> radioData; //хранит радиоданные по которым идёт вариант
    QVector<QString> svaz;//хранит связи между РТР
    QVector<int> intervalSvyazi;
    QVector<QString> nowKanalsVariants;
    QVector<QString> nowKanalsTimes;
    QVector<QString> boolSvaz; //хранит информацию о цвете линии соединения в данный момент
    int kol;
    int maxR=0;
    int kolConditions=0;
    QVector<int> intervalCondition;
    QVector<int> variantCondition;
    explicit TextOut(QObject *parent = 0);//конструктор
    int getSomeProperty()const;
    int getMaxRProperty()const;
    void changeBool(bool *t);
    void setSomeProperty(const int &);
    void setMaxRProperty(const int &);
    void changeString(QString *s,QString er);
    void sortMax(int *a,int *b);
    Q_INVOKABLE void perehodPoisk(int a, int nowTime);
    Q_INVOKABLE bool dalSvaz(int a, int b);
    Q_INVOKABLE QString sendColor(int a,int b);
    Q_INVOKABLE void getColor(int a,int b,QString s);
    Q_INVOKABLE QString readFile(int t);
    Q_INVOKABLE bool isSvaz(int a, int b);
    void maxRange(int *t);
    Q_INVOKABLE QString rasprRange();
    Q_INVOKABLE int maxKolRange();//максимальное колличество ртр в ранге
    Q_INVOKABLE int kolAll();//колличество всех приёмников ртр и приёмников
    Q_INVOKABLE QString vidVariant(int a);
    Q_INVOKABLE int timeCondition(int a);
    Q_INVOKABLE int kolCon();
    Q_INVOKABLE int maxConTime();

signals:
    void somePropertyChanged();
    void someMaxRChanged();


};


#endif // TEXTOUT_H
