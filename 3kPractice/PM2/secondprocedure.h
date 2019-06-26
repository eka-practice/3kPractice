#ifndef SECONDPROCEDURE_H
#define SECONDPROCEDURE_H
#include <QVector>
#include "database.h"
#include "source.h"
#include "receiver.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
// danilagribkov@bk.ru - Даниил
//Класс для работы второй процедуры
QT_CHARTS_USE_NAMESPACE
class secondprocedure
{
public:
    secondprocedure();
    QChartView* CreateFirstDiagramm();
    QChartView* CreateSecondDiagramm();
    QChartView* CreateThirdDiagramm();
    QChartView* CreateFourthDiagramm();
    static int randomBetween(int low, int high)
    {
        return (qrand() % ((high + 1) - low) + low);
    }
private:
    int run_counter = 1000; //Счетчик прогонов
    QVector<QVector<int>*> *source_number; //Ячейки,соответствующие номерам источников
    QVector<QVector<float>*> *time_number; //Ячейки плотности распределения времени
    QVector<QVector<float>*> *Pk; //Вероятность получения сообщения примеником в условиях У от к-го источника
    QVector<QVector<float>*> *Pi;// Вероятность получения сообщения приемником в условиях У за время в границах i-й ячейки
    int source_count; // Подсчет источников
    Database *dt;
    QVector<source*>* sources;
    QChartView *chartView;
};

#endif // SECONDPROCEDURE_H
