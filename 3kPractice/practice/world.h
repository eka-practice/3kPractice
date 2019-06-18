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
    World(QStringList* IDs, unsigned int radioNum, int modelTime = 0);
    World(QStringList *IDs, QVector<unsigned int>* radioNum, int modelTime = 0);

    ~World();
    // Старт модели
    void modelStart();

    QVector<AbstractSource*>* getSources() { return sources; }

    // get/set функции
    static int getModelTime() { return modelTime; }

    static int getSyncedOnce();
    static void setSyncedOnce(bool b);

    static int getMessageReceived();
    static void setMessageReceived(bool b);

    static int getLastWorkingInterval();
    static void setLastWorkingInterval(int num);

    static float getSyncCancelledTime();
    static void setSyncCancelledTime(float time);

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

    static float syncCancelled; // Модельное время завершения процесса синхронизации

private slots:
    void worldTick();
    void startTimer();
    void messageReceivedSlot();

signals:
    void ticked(); // TODO: Должен передавать source'ы
};

#endif // WORLD_H
