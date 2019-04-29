#ifndef ABSTRACTRECEIVER_H
#define ABSTRACTRECEIVER_H

#include <QVector>
#include <QSqlRecord>
#include <QVariant>
#include <QRandomGenerator>
#include "log.h"
#include "baseobject.h"

class World;
class AbstractSource;
class AbstractReceiver : public BaseObject
{
    Q_OBJECT

    friend class World;

public:
    AbstractReceiver(QSqlRecord DBRecord);
    virtual ~AbstractReceiver() override;

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

    void SyncedCalcs(QVector<AbstractSource*> *sources);

private:
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

	AbstractSource *curSrc;

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
