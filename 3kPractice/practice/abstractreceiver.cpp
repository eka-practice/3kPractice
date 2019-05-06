#include "info.h"

AbstractReceiver::AbstractReceiver(QSqlRecord DBRecord)
{
    // Считывание переменных из записи БД
    Num = DBRecord.value(0).toUInt();
    QVector<unsigned int> seq;
    QStringList seqStr = DBRecord.value(1).toString().split("|");
    for (int i = 0; i < seqStr.length(); i++) {
        seq.push_back(seqStr.at(i).toUInt());
    }
    sequence = seq;
    n0 = DBRecord.value(2).toUInt();
    seq.clear();
    seqStr.clear();
    curRadioNum = int(n0);
}

void AbstractReceiver::tick(QVector<AbstractSource*> *sources)
{
    if (started) {
		if (isSynced()) {
            if (!World::getMessageReceived() && curSrc->getCurRepeat() < int(curSrc->getMaxRepeatCount())) {
				if (float(int(QRandomGenerator::global()->generate()) % 100) / 100 < curSrc->getFMessageSent(curSrc->getCurRepeat())) {
					// Запись типа 4
                    Log::printMessage("ПСО 0 " + QString::number(curSrc->getK()) + " " + QString::number(World::getSyncCancelledTime() + EstimatedTimeToReceive));
                    World::setMessageReceived(true);

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
                curCoincidenceNum = 0;
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
            for (int i = curCoincidenceNum; i < World::getLastWorkingInterval(); i++) {
                bool F = false;
                for (int j = 0; j < sources->length(); j++) {
                    if (sequence[curRadioNum] == sources->at(j)->getK()) {
                        curCoincidenceNum = World::getModelTime(); // Найдено совпадение в такое время модели
                        // Запись типа 1
                        Log::printMessage("НС 0 " + QString::number(sources->at(j)->getK()) + " " + QString::number(World::getModelTime()));
                        setSyncing(true);
                        F = true;
                        break;
                    }
                }
                if (F) {
                    break;
                }
            }
        }

		// Если попытка синхронизации началась
		if (isSyncing() && !isSynced()) {
            // Разыгрываем вероятность синхронизации
            AbstractSource* curSource = sources->at(getCurCoincidenceSourceNum());
            if (float(int(QRandomGenerator::global()->generate()) % 100) / 100 < curSource->getMaxSyncProbability()) {
				// Запись типа 2
                Log::printMessage("УС 0 " + QString::number(sequence[curRadioNum]) + " " + QString::number(World::getModelTime()));

				// имитация сигнала об успешной синхронизации
                emit syncSuccess();

                SyncedCalcs(sources);

				setSynced(true);
                World::setSyncedOnce(true);
                //World::setMessageReceived(true);

			}
			else {
				// Запись типа 3
                Log::printMessage("НУС 0 " + QString::number(sequence[curRadioNum]) + " " + QString::number(World::getModelTime()));
				setSyncing(false);

				// имитация сигнала об ошибке синхронизации
                emit syncFailed();
			}
        }

        // Переход к следующим радиоданным
        curRadioNum++;
        if (int(curRadioNum) >= sequence.length()) {
            curRadioNum = 1;
        }
    }
}

void AbstractReceiver::SyncedCalcs(QVector<AbstractSource*> *sources) {
    // Моделирование возможности потери синхронизации
	curSrc = sources->at(curCoincidenceSourceNum);
    int SyncLostTime = 0;
	for (int i = curSrc->getCurRepeat(); i < int(curSrc->getMaxRepeatCount()); i++) {
		if (float(int(QRandomGenerator::global()->generate()) % 100) / 100 >= curSrc->getFSyncLost(i)) {
			SyncLostTime = i + int(curSrc->getStartTime());
			break;
		}
    }
	float time1 = World::getSyncCancelledTime() + SyncLostTime;
	float time2 = curSrc->getBrokenTime();
	float time3 = curSrc->getStartTime() + curSrc->getMaxRepeatCount() * curSrc->getRepeatDuration();

	if (time1 < time2 && time1 < time3) {
		EstimatedTimeToReceive = SyncLostTime;
	}
	else if (time2 < time1 && time2 < time3) {
        EstimatedTimeToReceive = curSrc->getBrokenTime() - World::getSyncCancelledTime();
	}
	else if (time3 < time1 && time3 < time2) {
        EstimatedTimeToReceive = time3 - World::getSyncCancelledTime();
	}

    // Непонятно зачем эта переменная, если есть curRepeat и maxRepeatCount в источнике
    int EstimatedRepeatsCount = int(EstimatedTimeToReceive) / int(curSrc->getRepeatDuration()); // дельта П
}
