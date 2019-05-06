#ifndef ABSTRACTSOURCE_H
#define ABSTRACTSOURCE_H

#include "econdition.h"
#include <QSqlRecord>
#include <QVariant>
#include "baseobject.h"

// lor1113@yandex.ru - Андрей
// Класс для симуляции работы источника.

//class World;
class AbstractSource;
class AbstractSource : public BaseObject
{
    Q_OBJECT

    //friend class World;

public:
    /// Конструктор источника
    /// DBRecord - запись из БД об источнике
    AbstractSource(QSqlRecord DBRecord, QObject *parent = nullptr);
    virtual ~AbstractSource() override;

    // get-функции

    float getStartTime() { return startTime; }

	float getMaxSyncProbability() { return maxSyncProbability[condition]; }

    float getFSyncLost(int repeatNum) { return FSyncLost[repeatNum][condition]; }

	float getFMessageSent(int repeatNum) { return FMessageSent[repeatNum][condition]; }

    float getBrokenTime() { return brokenTime; }

    float getRepeatDuration() { return repeatDuration; }

    float getMaxWaitTime() { return maxWaitTime; }

    unsigned int getMaxRepeatCount() { return maxRepeatCount; }

    int getCurRepeat() { return curReapeat; }

    unsigned int getK() { return k; }

    float getSyncCancelledTime() { return syncCancelledTime; }

private:
    /// tick-функция
    void tick(int modelTime);

    ECondition condition; // У // Условия передачи
    unsigned int k; // K // Номер источника 1-99
    unsigned int Number; // №  // Номер объекта плучателя 1-99
    float Ak; // A(k) // Расстояние до источника
    float Bk; // B(k) // Азимут направления 0-360
    float startTime; // Тн(k) // Время начала передачи сообщения
    float repeatDuration; // tп(k) // Длительность повтора
    unsigned int maxRepeatCount; // П(k) // Предельно возможное число повторов 1-99
    float FMessageSent[99][conditionCount]; // Fд(k)(t;У) // Плотности распределения времени доведения сообщения
    float brokenTime; // Tп(k) // Время выхода из строя
    float maxSearchTime; // tис(k) // Предельное время поиска приёмника
    float maxSyncProbability[3]; // Pус(k, y) // Предельная вероятность синхронизации
    float maxWaitTime; // tож(k) // Предельное время ожидания при потере синхронизации
    float FSyncLost[99][conditionCount]; // Fпс(k)(t;У) // Плотности распределения времени потери синхронизации приёмника

    float syncCancelledTime; // Время конца синхронизации

    int curReapeat = 0; // Текущий номер повтора

    bool sending = false; // Отправляется ли сообщение

};

#endif // ABSTRACTSOURCE_H
