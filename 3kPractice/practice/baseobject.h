#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <QObject>

// lor1113@yandex.ru - Андрей
// Базовый класс всех устройств. Содержит основные функции каждого устройства. (start, stop и т. д.) От него наследуются все устройства

class BaseObject : public QObject
{
    Q_OBJECT
public:
    explicit BaseObject(QObject *parent = nullptr);

    bool isStarted() { return started; }

    void start();
    void stop();

    unsigned int getID() { return ID; }

protected:
    bool started = false;
    unsigned int ID;
    int deviceType;

public slots:

signals:
	void workStarted();
	void workStopped();

};

#endif // BASEOBJECT_H
