#ifndef WORLD_H
#define WORLD_H

#include <QTimer>
#include <QThread>
#include <QApplication>
#include "database.h"

class AbstractReceiver;
class AbstractSource;
class World : public QObject
{
    Q_OBJECT

public:
    World();
    ~World();

    void modelStart();

    static int getModelTime() { return modelTime; }

    static int getSyncedOnce();
    static void setSyncedOnce(bool b);
    static int getMessageReceived();
    static void setMessageReceived(bool b);

    static int getLastWorkingInterval();
    static void setLastWorkingInterval(int num);

    static float getSyncCancelledTime();

    const int worldDeltaSeconds = 1000; // Постоянная для тика времени - 1000мс
    int timePerTick = 1000; // Время, проходящее в модели за тик // Можно будет менять для изменения скорости мира

private:
    QTimer *timer;
    QThread *thread;
    static int modelTime;

    bool started = false;

    static int lastWorkingInterval; // Последний интервал времени

    static bool syncedOnce;
    static bool messageReceived;

    AbstractReceiver *receiver;
    QVector<AbstractSource*> sources;

    Database *db;

    static float syncCancelled; // Модельное время завершения процесса синхронизации

private slots:
    void worldTick();
    void startTimer();
};

#endif // WORLD_H
