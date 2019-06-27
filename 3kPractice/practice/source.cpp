#include "source.h"

Source::Source(QSqlRecord DBRecord)
{
    k = DBRecord.value(K).toInt();
    startTime = DBRecord.value(START_TIME).toInt();
    repeatDuration = DBRecord.value(REPEAT_DURATION).toInt();
    maxRepeatCount = DBRecord.value(MAX_REPEAT_COUNT).toInt();
    influenceTime = DBRecord.value(INFLUENCE_TIME).toInt();
    influenceProbability = DBRecord.value(INFLUENCE_PROBABILITY).toFloat();
}
