#include "world.h"
#include "abstractreceiver.h"
#include "abstractsource.h"
#include "retranslator.h"

int World::modelTime = 1;
bool World::syncedOnce = false;
bool World::messageReceived = false;
int World::lastWorkingInterval = 0;
int World::syncCancelled = 0;
int World::curChannel = 0;

World::World()
{
    // Подключение к БД
    db = new Database();

    db->connectToDataBase("Data.db");

    QSqlQuery *qry = new QSqlQuery();
    sources = new QVector<AbstractSource*>();

    radioNums = new QVector<int>();

    qry->prepare("SELECT * FROM DEVICES");
    qry->exec();
    while (qry->next()) {
        if (qry->value(DEVICE_TYPE).toInt() == 1) { // тип устройства - приёмник
            receiver = new AbstractReceiver(qry->record(), sources, this);
            QStringList lst = qry->value(N0).toString().split("|");
            for (int i = 0; i < lst.length(); i++) {
                radioNums->append(lst.at(i).toInt());
            }
        }
        else if (qry->value(DEVICE_TYPE).toInt() == 0) { // источник
            AbstractSource *newSrc = new AbstractSource(qry->record(), this);
            sources->push_back(newSrc);

            if (newSrc->getSyncCancelledTime() > getLastWorkingInterval()) {
                setLastWorkingInterval(int(newSrc->getBrokenTime()));
            }
        }
        else { // ретранслятор
            Retranslator *newSrc = new Retranslator(qry->record(), sources, this);
            sources->push_back(newSrc->getSource());

            if (newSrc->getSource()->getSyncCancelledTime() > getLastWorkingInterval()) {
                setLastWorkingInterval(int(newSrc->getSource()->getBrokenTime()));
            }
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
    Log::CleanLogFile("output.txt");

    // Старт модели
    modelStart();

    connect(receiver, SIGNAL(messageReceived()), this, SLOT(messageReceivedSlot())); // Должен коннектить не только приёмник
    connect(receiver, SIGNAL(messageNotReceived()), this, SLOT(messageNotReceivedSlot()));

    receiveTime = new QVector<int>();
    curChannel = 1;
}

World::World(QStringList *IDs, QVector<int>* radioNum, int modelTime)
{
    // Подключение к БД
    db = new Database();

    db->connectToDataBase("Data.db");

    QSqlQuery *qry = new QSqlQuery();
    sources = new QVector<AbstractSource*>();

    qry->prepare("SELECT * FROM DEVICES");
    qry->exec();

    QSqlRecord receiverRecord;

    while (qry->next()) {
        if (IDs->contains(qry->value(D_ID).toString())) {
            if (qry->value(DEVICE_TYPE).toInt() == 1 || qry->value(D_ID) == IDs->last()) {
                receiverRecord = qry->record();
            }
            else if (qry->value(DEVICE_TYPE).toInt() == 0) { // источник
                AbstractSource *newSrc = new AbstractSource(qry->record(), this);
                sources->push_back(newSrc);

                if (newSrc->getSyncCancelledTime() > getLastWorkingInterval()) {
                    setLastWorkingInterval(int(newSrc->getBrokenTime()));
                }
            }
            else { // ретранслятор
                Retranslator *newSrc = new Retranslator(qry->record(), sources, this);
                sources->push_back(newSrc->getSource());


                connect(newSrc->getReceiver(), SIGNAL(messageReceived()), this, SLOT(messageReceivedSlot()));
                connect(newSrc->getReceiver(), SIGNAL(messageNotReceived()), this, SLOT(messageNotReceivedSlot()));

                if (newSrc->getSource()->getSyncCancelledTime() > getLastWorkingInterval()) {
                    setLastWorkingInterval(int(newSrc->getSource()->getBrokenTime()));
                }
            }
        }
    }

    AbstractSource* F = nullptr;
    for(int i = 0; i < sources->length(); i++) {
        if (sources->at(i)->getID() == receiverRecord.value(D_ID)) {
            F = sources->at(i);
            break;
        }
    }
    if (F == nullptr) {
        receiver = new AbstractReceiver(receiverRecord, sources, radioNum->at(0), this);
    }
    else {
        receiver = static_cast<Retranslator*>(F->parent())->getReceiver();
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
    Log::CleanLogFile("output.txt");

    this->modelTime = modelTime;

    // Старт модели
    modelStart();

    connect(receiver, SIGNAL(messageReceived()), this, SLOT(messageReceivedSlot())); // Должен коннектить не только приёмник
    connect(receiver, SIGNAL(messageNotReceived()), this, SLOT(messageNotReceivedSlot()));

    receiveTime = new QVector<int>();
    curChannel = 1;
    radioNums = radioNum;
}

void World::messageReceivedSlot() {
    receiveTime->append(getModelTime());
    if (curChannel < receiver->getChannelsNum()) {
        modelRestart();
        curChannel++;
    }
    else {
        // calcMinTime();
    }
}

void World::messageNotReceivedSlot() {
    if (curChannel < receiver->getChannelsNum()) {
        modelRestart();
    }
    else {
        // calcMinTime();
    }
}

void World::calcMinTime() {
    Log::CleanLogFile("output.txt");
    if (receiveTime->length() > 0) {
        int n = receiveTime->at(0);
        for (int i = 1; i < receiveTime->length(); i++) {
            if (receiveTime->at(i) < n) {
                n = receiveTime->at(i);
            }
        }
        Log::printMessage(QString::number(n), false, true, "output.txt");
    }
//    else {
//        Log::printMessage("-1", false, true, "output.txt");
//    }
    QApplication::exit();
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

void World::modelRestart()
{
    started = true;
    setModelTime(0);
    receiver->setN0(radioNums->at(curChannel));
    receiver->restart();
    receiver->start();
    for (int i = 0; i < sources->length(); i++) {
        sources->at(i)->restart();
    }
    messageReceived = false;
}

void World::worldTick() {
    if (started) {

		// Добавление времени модели
        World::modelTime += 1;
        emit ticked();

        for (int i = 0; i < sources->length(); i++) {
            if (sources->at(i)->isStarted()) {
                return;
            }
        }
        if (modelTime > lastWorkingInterval) {
            started = false;
        }
    }
    else {
        calcMinTime();
        QApplication::exit();
    }
}

int World::getSyncedOnce() { return syncedOnce; }
void World::setSyncedOnce(bool b) { syncedOnce = b; }

int World::getMessageReceived() { return messageReceived; }
void World::setMessageReceived(bool b) { messageReceived = b; }

int World::getLastWorkingInterval() { return lastWorkingInterval; }
void World::setLastWorkingInterval(int num) { lastWorkingInterval = num; }

int World::getSyncCancelledTime() { return syncCancelled; }
void World::setSyncCancelledTime(int time) { syncCancelled = time; }
