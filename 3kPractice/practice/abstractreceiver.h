#ifndef ABSTRACTRECEIVER_H
#define ABSTRACTRECEIVER_H

#include <QVector>
#include <QSqlRecord>
#include <QVariant>
#include <QRandomGenerator>
#include "log.h"
#include "baseobject.h"

// lor1113@yandex.ru - Андрей
// Класс для симуляции работы приёмника.

class World;
class AbstractSource;
class AbstractReceiver : public BaseObject
{
    Q_OBJECT

    friend class World; // По сути нужен только для того, чтобы вызвать в World'е метод tick из этого класса
    // Нашёл пример как можно сделать без этого - через template class, записывать сюда ссылку на владельца объекта. Позже попробую

public:
    /// Конструктор приёмника
    /// DBRecord - запись базы данных об этом приёмнике
    AbstractReceiver(QSqlRecord DBRecord);
    virtual ~AbstractReceiver() override {}

    // get/set функции

    bool isSyncing() { return syncing; }
    void setSyncing(bool s) { syncing = s; }

    bool isSynced() { return synced; }
    void setSynced(bool s) { synced = s; }

    void setN(unsigned int n) { Num = n; }
    void setSeq(QVector<unsigned int> s) { sequence = s; }
    void setN0(unsigned int n) { n0 = n; }

	int getCurCoincidenceNum() { return curCoincidenceNum; }
	void setCurCoincidenceNum(int num) { curCoincidenceNum = num; }

    int getCurCoincidenceSourceNum() { return curCoincidenceSourceNum; }

    /// Функция вычислений после синхронизации с источником
    void SyncedCalcs(QVector<AbstractSource*> *sources);

private:
    /// tick-функция
    void tick(QVector<AbstractSource*> *sources);

    unsigned int Num; // N // Число радиоданных
    QVector<unsigned int> sequence; // k1->k2->k3->...kn->k1 // Порядок следования радиоданных
    unsigned int n0; // n0 // Порядковый номер радиоданных приёмника на нулевое модельное время

    bool syncing = false; // Флаг попытки синхронизации
    bool synced = false; // Флаг синхронизации

	int curCoincidenceNum = 0; // Текущее совпадение
	int curCoincidenceSourceNum = 0; // Номер источника совпадения

    float EstimatedTimeToReceive = 0;
    float newSyncCicleTime = 0;

    AbstractSource *curSrc; // Текущий источник, с которым работает приёмник

    int curRadioNum; // Текущий номер радиоданных в последовательности

signals:
	void syncSuccess();
	void syncFailed();
	void messageReceived();
    void messageNotReceived();
	void receivingStarted();
	void receivingStopped();
};

#endif // ABSTRACTRECEIVER_H
