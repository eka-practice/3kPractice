#ifndef FIRSTPROCEDURE_H
#define FIRSTPROCEDURE_H
#include <QVector>
#include "database.h"
#include "source.h"
#include "receiver.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

// danilagribkov@bk.ru - Даниил

QT_CHARTS_USE_NAMESPACE
// danilagribkov@bk.ru - Даниил
//Класс для первой процедуры
class Firstprocedure
{
public:
    Firstprocedure();

    QChartView* CreateFirstDiagramm();
    QChartView* CreateSecondDiagramm();
    int randomBetween(int low, int high)
    {
        return (qrand() % ((high + 1) - low) + low);
    }

private:
    int run_counter = 1000; //Счетчик прогонов
    QVector<int> *source_number; //Ячейки,соответствующие номерам источников
    QVector<float> *time_number; //Ячейки плотности распределения времени
    QVector<float> *Pk; //Вероятность получения сообщения примеником в условиях У от к-го источника
    QVector<float> *Pi;// Вероятность получения сообщения приемником в условиях У за время в границах i-й ячейки
    int source_count; // Подсчет источников
    Database *dt;
    QVector<source*>* sources;

    QChartView *chartView;
};

#endif // FIRSTPROCEDURE_H
