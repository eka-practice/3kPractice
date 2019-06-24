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

class AbstractSource;
class AbstractReceiver : public BaseObject
{
    Q_OBJECT

public:
    // Конструктор приёмника
    // DBRecord - запись базы данных об этом приёмнике
    AbstractReceiver(QSqlRecord DBRecord, QVector<AbstractSource*> *sources, QObject *parent = nullptr); // Для полного считывания из базы
    // Для вызова из другой программы
    AbstractReceiver(QSqlRecord DBRecord, QVector<AbstractSource *> *sources, QVector<unsigned int>* radioNum, QObject *parent = nullptr);
    AbstractReceiver(QSqlRecord DBRecord, QVector<AbstractSource*> *sources, unsigned int radioNum, QObject *parent = nullptr);
    virtual ~AbstractReceiver() override {}

    // get/set функции

    void setN(unsigned int n) { Num = n; }
    void setSeq(QVector<unsigned int>* s) { sequence = s; }
    void setN0(unsigned int n, int i) { n0->removeAt(i); n0->insert(i, n); }

    // Из-за каналов - все функции принимают номер канала
    bool isSyncing() { return syncing; }
    void setSyncing(bool s) { syncing = s; }

    bool isSynced() { return synced; }
    void setSynced(bool s) { synced = s; }

    int getCurCoincidenceNum() { return curCoincidenceNum; }
    void setCurCoincidenceNum(int num) { curCoincidenceNum = num; }

    int getCurCoincidenceSourceNum() { return curCoincidenceSourceNum; }

    // Функция вычислений после синхронизации с источником
    void SyncedCalcs(QVector<AbstractSource*> *sources);

protected slots:
    // tick-функция
    void tick();

private:
    unsigned int Num; // N // Число радиоданных
    QVector<unsigned int>* sequence; // k1->k2->k3->...kn->k1 // Порядок следования радиоданных
    QVector<unsigned int>* n0; // n0 // Порядковый номер радиоданных приёмника на нулевое модельное время /// Поидее тоже вектор
    int channelsNum; // Кол-во каналов в приёмнике
    int searchInterval; // tип // Интервал поиска

    int nextIntervalEnd; // Конец следующего интервала поиска

    bool syncing = false; // Флаг попытки синхронизации
    bool synced = false; // Флаг синхронизации

    int curCoincidenceNum = 0; // Текущее совпадение
    int curCoincidenceSourceNum = 0; // Номер источника совпадения

    int EstimatedTimeToReceive = 0;
    int newSyncCicleTime = 0;

    AbstractSource *curSrc; // Текущий источник, с которым работает приёмник

    QVector<unsigned int>* curRadioNum; // Текущий номер радиоданных в последовательности
    unsigned int syncingNum;

    QVector<AbstractSource*> *sources; // Все источники мира

    void notSynced();

signals:
	void syncSuccess();
	void syncFailed();
	void messageReceived();
    void messageNotReceived();
	void receivingStarted();
	void receivingStopped();
};

#endif // ABSTRACTRECEIVER_H
