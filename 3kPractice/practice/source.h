#ifndef SOURCE_H
#define SOURCE_H

#include <QSqlRecord>
#include "database.h"

class Source
{
public:
    Source(QSqlRecord DBRecord);

    int getK() { return k; }

    float getInfluenceProbability() { return influenceProbability; }

    int getInfluenceTime() { return influenceTime; }

    int getStartTime() { return startTime; }

    int getRepeatDuration() { return repeatDuration; }

    int getMaxRepeatCount() { return maxRepeatCount; }

private:
    int k; // K // Номер источника 1-99
    int startTime; // Тн(k) // Время начала передачи сообщения
    int repeatDuration; // tп(k) // Длительность повтора
    int maxRepeatCount; // П(k) // Предельно возможное число повторов 1-99
    int influenceTime; // Tв(k) // Время воздействия по k-му источнику
    float influenceProbability; // Pп(k) // Вероятность поражения
};

#endif // SOURCE_H
