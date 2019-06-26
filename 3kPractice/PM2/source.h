#ifndef SOURCE_H
#define SOURCE_H
#include <QSqlRecord>
// danilagribkov@bk.ru - Даниил
// Класс источника
class source
{
public:
    source();
    source(QSqlRecord DBRecord);
    float getStartTime() {return startTime;}
    float getRepeatDuration() {return repeatDuration;}
    unsigned int getMaxRepeatCount() {return maxRepeatCount;}
private:
     unsigned int k; // K // Номер источника 1-99
    float startTime; // Тн(k) // Время начала передачи сообщения
    float repeatDuration; // tп(k) // Длительность повтора
    unsigned int maxRepeatCount; // П(k) // Предельно возможное число повторов 1-99
};

#endif // SOURCE_H
