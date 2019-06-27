#ifndef WORKINGCLASS_H
#define WORKINGCLASS_H

#include <QVector>
#include "source.h"
#include "database.h"
#include <QTimer>
#include <QThread>


class WorkingClass
{
public:
    WorkingClass();

    void modelStart();

    const int cellCount = 20;

private:
    int X; // Счётчик числа прогонов
    int maxX; // Нужное число прогонов
    QVector<QVector<float>> *PTime; // Ячейки плотности распределения времени
    QVector<QVector<int>> *receivedSources; // Ячейки, соответствующие номерам источников от которых получено сообщение
    QVector<QVector<int>*> *sequences; // Ряды радиоданных
    QVector<QVector<int>*> *n0; // Ряды начальных радиоданных
    QVector<Source*> *sources; // Источники

    QVector<QVector<float>*>* timeRows; // Ряд распределения времени (От Гриба)
    QVector<QVector<float>*>* mReceivePeriodicity; // Частоты получения сообщения (От Гриба)

    // Тп(K) - время поражения??
    QVector<int>* brokenTime;

    Database *db;

    bool started = false;
};

#endif // WORKINGCLASS_H
