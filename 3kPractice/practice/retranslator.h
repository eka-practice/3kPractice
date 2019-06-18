#ifndef RETRANSLATOR_H
#define RETRANSLATOR_H

#include "abstractsource.h"
#include "abstractreceiver.h"
#include <QObject>

class Retranslator : public BaseObject
{
    Q_OBJECT

public:
    Retranslator(QSqlRecord DBRecord, QVector<AbstractSource*> *sources, QObject *parent = nullptr);

    virtual ~Retranslator() override {}

    AbstractSource* getSource() { return source; }
    AbstractReceiver* getReceiver() { return receiver; }

private slots:
    // tick-функция
    void tick();

private slots:
    void receiverStopped();
    void received();

private:
    AbstractReceiver* receiver;
    AbstractSource* source;

    float repeatDelay; // Задержка ретрансляции
    float repeatTime;
    bool mReceived;

signals:
    void ticked();
};

#endif // RETRANSLATOR_H
