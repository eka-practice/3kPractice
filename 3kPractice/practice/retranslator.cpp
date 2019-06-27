#include "retranslator.h"
#include "world.h"

Retranslator::Retranslator(QSqlRecord DBRecord, QVector<AbstractSource*> *sources, QObject *parent) : BaseObject (parent)
{
    // Читаем из базы
    ID = DBRecord.value(D_ID).toUInt();
    source = new AbstractSource(DBRecord, this);
    receiver = new AbstractReceiver(DBRecord, sources, parent);

    source->setStartTime(-1);
    deviceType = 2;

    // Подключаем к паренту
    World *w = static_cast<World*>(parent);
    connect(w, SIGNAL(ticked()), this, SLOT(tick()));

    connect(receiver, SIGNAL(workStopped()), this, SLOT(receiverStopped()));
    connect(receiver, SIGNAL(messageReceived()), this, SLOT(received()));

    start();
}

void Retranslator::tick()
{
    if (!this->receiver->isStarted()) {
        if (!this->source->isStarted() && mReceived && World::getModelTime() >= repeatTime) {
            this->source->start();
        }
    }
    emit ticked();
}

void Retranslator::receiverStopped()
{
    if (mReceived) {
        repeatTime = World::getModelTime() + repeatDelay;
    }
    else {
        stop();
    }
}

void Retranslator::received()
{
    mReceived = true;
}

void Retranslator::restart() {
    source->restart();
    receiver->restart();
}
