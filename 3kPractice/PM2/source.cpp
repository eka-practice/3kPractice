#include "source.h"
#include "database.h"
// danilagribkov@bk.ru - Даниил
source::source(QSqlRecord DBRecord)

{
    k = DBRecord.value(Ka).toUInt();
    startTime = DBRecord.value(START_TIME).toUInt();
    repeatDuration = DBRecord.value(REPEAT_DURATION).toUInt();
    maxRepeatCount = DBRecord.value(MAX_REPEAT_COUNT).toUInt();
}
