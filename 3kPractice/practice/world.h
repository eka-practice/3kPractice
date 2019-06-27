#ifndef WORLD_H
#define WORLD_H

#include <QTimer>
#include <QThread>
#include <QApplication>
#include "database.h"

// lor1113@yandex.ru - Андрей
// Класс мира для симуляции всей модели. Тут создаются и хранятся приёмники и источники, запускается их работа

class AbstractReceiver;
class AbstractSource;
class World : public QObject
{
    Q_OBJECT

public:
    World();
    World(QStringList *IDs, QVector<int>* radioNum, int modelTime = 0);

    ~World();
    // Старт модели
    void modelStart();

    void modelRestart();

    void calcMinTime();

    QVector<AbstractSource*>* getSources() { return sources; }

    // get/set функции
    static int getModelTime() { return modelTime; }
    static void setModelTime(int time) { modelTime = time; }

    static int getSyncedOnce();
    static void setSyncedOnce(bool b);

    static int getMessageReceived();
    static void setMessageReceived(bool b);

    static int getLastWorkingInterval();
    static void setLastWorkingInterval(int num);

    static int getSyncCancelledTime();
    static void setSyncCancelledTime(int time);

    static int getCurChannel() { return curChannel; }

    const int worldDeltaSeconds = 10; // Постоянная для тика времени - 1000мс

private:
    QTimer *timer;
    QThread *thread;
    static int modelTime;

    bool started = false;

    static int lastWorkingInterval; // Последний интервал времени

    static bool syncedOnce;
    static bool messageReceived;

    AbstractReceiver *receiver;
    QVector<AbstractSource*>* sources;

    Database *db;

    static int syncCancelled; // Модельное время завершения процесса синхронизации

    QVector<int>* receiveTime;

    QVector<int>* radioNums;
    static int curChannel;

private slots:
    void worldTick();
    void startTimer();
    void messageReceivedSlot();
    void messageNotReceivedSlot();

signals:
    void ticked(); // TODO: Должен передавать source'ы
};

#endif // WORLD_H
