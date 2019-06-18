#include "abstractsource.h"
#include "econdition.h"
#include "world.h"
#include "retranslator.h"

AbstractSource::AbstractSource(QSqlRecord DBRecord, QObject *parent) : BaseObject (parent)
{
    // Считывание переменных из записи БД
    ID = DBRecord.value(D_ID).toUInt();
    k = DBRecord.value(K).toUInt();
    // Парсим строку, в которой находится таблица временных интервалов
    conditions = new QVector<TimeInterval*>();
    QStringList strLst = DBRecord.value(CONDITION).toString().split('|');
    for (int i = 0; i < strLst.length(); i++) {
        QStringList recordStrLst = strLst[i].split(';');
        conditions->append(new TimeInterval {recordStrLst[0].toInt(), ECondition(recordStrLst[1].toInt())});
    }
    Number = DBRecord.value(NUMBER).toUInt();
    Ak = DBRecord.value(AK).toFloat();
    Bk = DBRecord.value(BK).toFloat();
    startTime = DBRecord.value(START_TIME).toFloat();
    repeatDuration = DBRecord.value(REPEAT_DURATION).toFloat();
    maxRepeatCount = DBRecord.value(MAX_REPEAT_COUNT).toUInt();
    // Парсим строку, в которой находится таблица распределения
    strLst = DBRecord.value(F_MESSAGE_SENT).toString().split('|');
    for (int i = 0; i < 99 && i < strLst.length(); i++) {
        QStringList recordStrLst = strLst[i].split(';');
        for (int j = 0; j < conditionCount; j++) {
            FMessageSent[i][j] = recordStrLst[j].toFloat();
        }
    }
    brokenTime = DBRecord.value(BROKEN_TIME).toFloat();
    maxSearchTime = DBRecord.value(MAX_SEARCH_TIME).toFloat();
    // Парсим строку со значениями вероятности синхронизации с источником
    strLst = DBRecord.value(MAX_SYNC_PROBABILITY).toString().split('|');
    for (int i = 0; i < conditionCount && i < strLst.length(); i++) {
        maxSyncProbability[i] = strLst[i].toFloat();
    }
    maxSearchTime = DBRecord.value(MAX_WAIT_TIME).toFloat();

    deviceType = 0;

    syncCancelledTime = startTime + maxSearchTime;

    World *w = static_cast<World*>(parent);

    if (w) {
        connect(w, SIGNAL(ticked()), this, SLOT(tick()));
    }
    else if (Retranslator *r = static_cast<Retranslator*>(parent)) {
        connect(r, SIGNAL(ticked()), this, SLOT(tick()));
    }
}

AbstractSource::~AbstractSource() {}

ECondition AbstractSource::getCondition(int time)
{
    for (int i = 0; i < conditions->length(); i++) {
        if (conditions->at(i)->time > time) { // Если мы дошли до нужного интервала
            return conditions->at(i)->condition;
        }
    }
    return conditions->last()->condition;
}

ECondition AbstractSource::getCondition()
{
    for (int i = 0; i < conditions->length(); i++) {
        if (conditions->at(i)->time > World::getModelTime()) { // Если мы дошли до нужного интервала
            return conditions->at(i)->condition;
        }
    }
    return conditions->last()->condition;
}

void AbstractSource::tick()
{
    if (started) {
        // Если время синхронизации вышло - заканчиваем её
        if (syncCancelledTime > World::getModelTime()) {
            sending = false;
            curReapeat = 0;
        }
        // Иначе - инкремент повтора
        else if (startTime <= World::getModelTime()) {
            sending = true;
            curReapeat++;
        }
    }
    else if (startTime != -1 && World::getModelTime() > startTime && World::getModelTime() < brokenTime) {
        start();
    }
}
