#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <QObject>

class BaseObject : public QObject
{
    friend class World;

    Q_OBJECT
public:
    explicit BaseObject(QObject *parent = nullptr);

    bool isStarted() { return started; }

private:
    //virtual void tick(int modelTime);

    void start();
    void stop();

protected:
    bool started = false;

public slots:

signals:
	void workStarted();
	void workStopped();

};

#endif // BASEOBJECT_H
