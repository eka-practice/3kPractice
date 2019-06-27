#include "baseobject.h"

BaseObject::BaseObject(QObject *parent) : QObject(parent)
{

}

void BaseObject::start() {
    if (!started) {
        started = true;
		emit workStarted();
    }
}

void BaseObject::stop() {
    if (started) {
        started = false;
		emit workStopped();
    }
}

void BaseObject::restart() {}
