#include "info.h"

AbstractSource::AbstractSource(QSqlRecord DBRecord) // DBRecord - передаём сюда запись из таблицы БД
{
    // Инициализируем все наши переменные
    k = DBRecord.value(0).toUInt();
    condition = ECondition(DBRecord.value(1).toInt());
    Number = DBRecord.value(2).toUInt();
    Ak = DBRecord.value(3).toFloat();
    Bk = DBRecord.value(4).toFloat();
    startTime = DBRecord.value(5).toFloat();
    repeatDuration = DBRecord.value(6).toFloat();
    maxRepeatCount = DBRecord.value(7).toUInt();
    // парсим строку, в которой находится таблица распределения
    QStringList strLst = DBRecord.value(8).toString().split('|');
    for (int i = 0; i < 99 && i < strLst.length(); i++) {
        QStringList recordStrLst = strLst[i].split(';');
        for (int j = 0; j < conditionCount; j++) {
            FMessageSent[i][j] = recordStrLst[j].toFloat();
        }
    }
    brokenTime = DBRecord.value(9).toFloat();
    maxSearchTime = DBRecord.value(10).toFloat();
    // Парсим строку со значениями вероятности синхронизации с источником
    strLst = DBRecord.value(11).toString().split('|');
    for (int i = 0; i < 3 && i < strLst.length(); i++) {
        maxSyncProbability[i] = strLst[i].toFloat();
    }
    maxSearchTime = DBRecord.value(12).toFloat();
    // парсим строку, в которой находится таблица распределения
    strLst = DBRecord.value(13).toString().split('|');
    for (int i = 0; i < 99 && i < strLst.length(); i++) {
        QStringList recordStrLst = strLst[i].split(';');
        for (int j = 0; j < conditionCount; j++) {
            FSyncLost[i][j] = recordStrLst[j].toFloat();
        }
    }

    syncCancelledTime = startTime + maxSearchTime; // Сделать вычисление в ресивере и set функцию в ворлде
}

AbstractSource::~AbstractSource() {}

void AbstractSource::tick(int modelTime)
{
    if (started) {
        if (syncCancelledTime > modelTime) {
            sending = false;
            curReapeat = 0;
        }
        else if (startTime <= modelTime) {
            sending = true;
            curReapeat++;
        }
    }
}
