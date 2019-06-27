#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

// lor1113@yandex.ru - Андрей
// Класс для работы с БД. Всё работает так же, как и в программе о алгоритму Дейкстры

// Директивы имен таблиц и их полей

#define TABLE_SOURCE            "Source"
#define TABLE_INPUT             "Input"

#define K                       "K"
#define START_TIME              "StartTime"
#define INFLUENCE_TIME          "InfluenceTime"
#define INFLUENCE_PROBABILITY   "InfluenceProbability"
#define REPEAT_DURATION         "RepeatDuration"
#define MAX_REPEAT_COUNT        "MaxRepeatCount"
#define CONDITION               "Condition"

#define RECEIVE_PROBABILITY     "ReceiveProbability"
#define SEQUENCE                "Sequence"
#define N0                      "n0"
#define DEVICE_TYPE             "C"

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database();
    void connectToDataBase(QString dbName);

private:
    QSqlDatabase      db;
    QString DataBaseName;

private:
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createDeviceTable();
};

#endif
