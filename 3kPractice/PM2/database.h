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

// danilagribkov@bk.ru - Даниил
// Класс для работы с БД.

// Директивы имен таблиц и их полей

#define TABLE_SOURCE            "Source"
#define TABLE_RECEIVER          "Receiver"
#define TABLE_DEVICES           "Devices"

#define D_ID                    "ID"
#define DEVICE_TYPE             "DeviceType"
#define Ka                       "K"
#define CONDITION               "Condition"
#define NUMBER                  "Number"
#define AK                      "Ak"
#define BK                      "Bk"
#define START_TIME              "StartTime"
#define REPEAT_DURATION         "RepeatDuration"
#define MAX_REPEAT_COUNT        "MaxRepeatCount"
#define F_MESSAGE_SENT          "FMessageSent"
#define BROKEN_TIME             "BrokenTime"
#define MAX_SEARCH_TIME         "MaxSearchTime"
#define MAX_SYNC_PROBABILITY    "MaxSyncProbability"
#define MAX_WAIT_TIME           "MaxWaitTime"
#define F_SYNC_LOST             "FSyncLost"
#define NUM                     "N"
#define SEQUENCE                "Sequence"
#define N0                      "n0"
#define CHANNELS_COUNT          "ChannelsCount"
#define SEARCH_INTERVAL         "SearchInterval"

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
