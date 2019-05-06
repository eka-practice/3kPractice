//#include "world.h"
#include <info.h>

int World::modelTime = 1;
bool World::syncedOnce = false;
bool World::messageReceived = false;
int World::lastWorkingInterval = 0;
float World::syncCancelled = 0;

World::World()
{
    // Подключение к БД
    db = new Database();

    db->connectToDataBase("Data.db");

    QSqlQuery *qry = new QSqlQuery();
    // Создание приёмников
    qry->prepare("SELECT * FROM Receiver");
    qry->exec();
    qry->first();

    receiver = new AbstractReceiver(qry->record(), this);

    // Создание источников
    qry->prepare("SELECT * FROM Source");
    qry->exec();

    while(qry->next()) {
        AbstractSource *newSrc = new AbstractSource(qry->record(), this);
        sources.push_back(newSrc);

        if (newSrc->getSyncCancelledTime() > getLastWorkingInterval()) {
            setLastWorkingInterval(int(newSrc->getSyncCancelledTime()));
        }
    }
    // Инициализация тик-таймера
    thread = new QThread();
    this->moveToThread(thread);
    timer = new QTimer();
    timer->setInterval(worldDeltaSeconds);
    connect(timer, SIGNAL(timeout()), this, SLOT(worldTick()));
    timer->moveToThread(thread);
    thread->start();
    QMetaObject::invokeMethod(this, "startTimer", Qt::QueuedConnection);
    Log::CleanLogFile();

    // Старт модели
    modelStart();
}

void World::startTimer() {
    timer->start();
}

World::~World() {

}

void World::modelStart()
{
    started = true;
}

void World::worldTick() {
    if (started) {
        // Запуск устройств
        if (!receiver->isStarted() && World::modelTime == 1) {
            receiver->start();
            //receiver->tick(&sources);
        }
        else {
            //receiver->tick(&sources);
        }
        for (int i = 0; i < sources.length(); i++) {
            if (sources.at(i)->isStarted()){
                //sources.at(i)->tick(World::modelTime);
            }
            else if (World::modelTime > sources.at(i)->getStartTime()) {
                sources.at(i)->start();
                //sources.at(i)->tick(World::modelTime);
            }
        }

		// Добавление времени модели
        World::modelTime += timePerTick / 1000;

        emit ticked();
    }
    else {
        QApplication::exit();
    }
}

int World::getSyncedOnce() { return syncedOnce; }
void World::setSyncedOnce(bool b) { syncedOnce = b; }
int World::getMessageReceived() { return messageReceived; }
void World::setMessageReceived(bool b) { messageReceived = b; }

int World::getLastWorkingInterval() { return lastWorkingInterval; }
void World::setLastWorkingInterval(int num) { lastWorkingInterval = num; }

float World::getSyncCancelledTime() { return syncCancelled; }
