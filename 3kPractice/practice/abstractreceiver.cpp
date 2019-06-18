#include "abstractreceiver.h"
#include "abstractsource.h"
#include "world.h"

AbstractReceiver::AbstractReceiver(QSqlRecord DBRecord, QVector<AbstractSource*> *sources, QObject *parent) : BaseObject (parent)
{
    // Считывание переменных из записи БД
    ID = DBRecord.value(D_ID).toUInt();
    Num = DBRecord.value(NUM).toUInt();
    QVector<unsigned int>* seq = new QVector<unsigned int>();
    QStringList seqStr = DBRecord.value(SEQUENCE).toString().split("|");
    for (int i = 0; i < seqStr.length(); i++) {
        seq->push_back(seqStr.at(i).toUInt());
    }
    sequence = seq;
    channelsNum = DBRecord.value(CHANNELS_COUNT).toInt();
    //n0 = DBRecord.value(N0).toUInt();
    n0 = new QVector<unsigned int>();
    seqStr = DBRecord.value(N0).toString().split('|');
    for (int i = 0; i < seqStr.length() && i < channelsNum; i++) {
        n0->push_back(seqStr.at(i).toUInt());
    }
    searchInterval = DBRecord.value(SEARCH_INTERVAL).toFloat();

    //seq->clear();
    seqStr.clear();
    curRadioNum = n0;
    nextIntervalEnd = searchInterval;

    deviceType = 1;

    this->sources = sources;

    World *w = static_cast<World*>(parent);

    connect(w, SIGNAL(ticked()), this, SLOT(tick()));

    start();
}

AbstractReceiver::AbstractReceiver(QSqlRecord DBRecord, QVector<AbstractSource *> *sources, QVector<unsigned int>* radioNum, QObject *parent) : AbstractReceiver(DBRecord, sources, parent)
{
    n0 = radioNum;
    curRadioNum = n0;
}

AbstractReceiver::AbstractReceiver(QSqlRecord DBRecord, QVector<AbstractSource *> *sources, unsigned int radioNum, QObject *parent) : AbstractReceiver(DBRecord, sources, parent)
{
    n0->append(radioNum);
    curRadioNum = n0;
}

void AbstractReceiver::tick()
{
    if (started) {
        if (isSynced()) {
            if (!World::getMessageReceived() && curSrc->getCurRepeat() < int(curSrc->getMaxRepeatCount())) { // Дельта П??
                if (float(int(QRandomGenerator::global()->generate()) % 100) / 100 < curSrc->getFMessageSent(curSrc->getCurRepeat())) {
                    // Запись типа 4
                    Log::printMessage("ПСО 0 " + QString::number(curSrc->getK()) + " " + QString::number(World::getSyncCancelledTime() + EstimatedTimeToReceive));
                    World::setMessageReceived(true);

                    Log::printMessage(QString::number(World::getModelTime()), false, true, "output.txt"); // Фиксируем время получения сообщени

                    emit messageReceived(); // Имитация сигнала о принятии сообщения

                    // Завершение работы алгоритма
                    started = false;
                    return;
                }
            }
            else if (!World::getMessageReceived()) {
                // Запись типа 5
                Log::printMessage("ПСИ 0 " + QString::number(curSrc->getK()) + " " + QString::number(World::getSyncCancelledTime() + EstimatedTimeToReceive));
                // Определение нового цикла синхронизации с другими источниками
                newSyncCicleTime = World::getSyncCancelledTime() + EstimatedTimeToReceive + curSrc->getMaxWaitTime();
                setCurCoincidenceNum(0);
                setSynced(false);
                setSyncing(false);
            }
        }

        // Если всё время закончилось
        if (World::getModelTime() >= World::getLastWorkingInterval()) {
            if (!isSynced() && !isSyncing() && !World::getMessageReceived()) {
                // Запись типа 6
                Log::printMessage("НПС 0 " + QString::number(World::getModelTime()));

                // Завершение работы алгоритма
                started = false;
                return;
            }
        }

        // Если перешли за время старта синхронизации - ищем новое время синхронизации
        if (curCoincidenceNum < World::getModelTime() && !isSyncing() && newSyncCicleTime < World::getModelTime()) {
            for (curCoincidenceNum; curCoincidenceNum < World::getLastWorkingInterval() && curCoincidenceNum < nextIntervalEnd; curCoincidenceNum++) {
            //if (curCoincidenceNum < World::getLastWorkingInterval()) {
                bool F = false;
                for (int i = 0; i < channelsNum; i++) {
                    for (int k = 0; k < sources->length(); k++) {
                        if (sequence->at(curRadioNum->at(i)) == sources->at(k)->getK() && sources->at(k)->isStarted()) {
                            curCoincidenceNum++;
                            curCoincidenceSourceNum = k;
                            // Запись типа 1
                            Log::printMessage("НС 0 " + QString::number(sources->at(k)->getK()) + " " + QString::number(curCoincidenceNum));
                            ///World::setSyncCancelledTime(curSrc->getSyncCancelledTime()); // Непонятная система с этим Тзс
                            setSyncing(true);
                            F = true;
                            syncingNum = curRadioNum->at(i);
                            break;
                        }
                    }
                    if (F) break;
                }
                if (F) break;
            }
        }

        // Если попытка синхронизации началась
        if (isSyncing() && !isSynced() && curCoincidenceNum <= World::getModelTime()) {
            // Разыгрываем вероятность синхронизации
            AbstractSource* curSource = sources->at(getCurCoincidenceSourceNum());
            if (float(int(QRandomGenerator::global()->generate()) % 100) / 100 < curSource->getMaxSyncProbability() && World::getSyncCancelledTime() < curSource->getSyncCancelledTime()/*Тзс мира < конца передачи источником (То ли это время??)*/) {
                // Запись типа 2
                Log::printMessage("УС 0 " + QString::number(sequence->at(int(syncingNum))) + " " + QString::number(World::getModelTime()));

                // Имитация сигнала об успешной синхронизации
                emit syncSuccess();

                SyncedCalcs(sources);

                setSynced(true);
                World::setSyncedOnce(true);
            }
            else {
                // Запись типа 3
                Log::printMessage("НУС 0 " + QString::number(sequence->at(int(syncingNum))) + " " + QString::number(World::getModelTime()));
                setSyncing(false);

                // имитация сигнала об ошибке синхронизации
                emit syncFailed();
            }
        }

        // Переход к следующим радиоданным
        if (World::getModelTime() >= nextIntervalEnd) {
            if (!syncing) { // Если идёт синхронизация - не меняем радиоданные
                for (int i = 0; i < channelsNum; i++) {
                    unsigned int num = curRadioNum->at(i) + 1;
                    curRadioNum->removeAt(i);
                    curRadioNum->insert(i, num);
                    if (int(curRadioNum->at(i)) >= sequence->length()) {
                        curRadioNum->removeAt(i);
                        curRadioNum->insert(i, 0); /// Может 0, а не 1??
                    }
                }
            }
            nextIntervalEnd += searchInterval;
        }
    }
}

void AbstractReceiver::SyncedCalcs(QVector<AbstractSource*> *sources) { // Подумать можно ли сделать 1 источник, сохранить в переменную локальную
    AbstractSource* src = sources->at(curCoincidenceSourceNum);
    curSrc = src;
    float time1 = src->getBrokenTime();
    float time2 = src->getStartTime() + src->getMaxRepeatCount() * src->getRepeatDuration();

    if (time1 < time2) {
        EstimatedTimeToReceive = time1 - World::getSyncCancelledTime();
	}
    else {
        EstimatedTimeToReceive = time2 - World::getSyncCancelledTime();
	}

    // Непонятно зачем эта переменная, если есть curRepeat и maxRepeatCount в источнике
    int EstimatedRepeatsCount = int(EstimatedTimeToReceive) / int(src->getRepeatDuration()); // дельта П
}
