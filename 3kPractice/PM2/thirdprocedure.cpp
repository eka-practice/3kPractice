#include "thirdprocedure.h"
#include "source.h"
#include <QtMath>
#include "data.h"
#include <QMainWindow>
#include <QApplication>
#include <QtWidgets/QMainWindow>
// danilagribkov@bk.ru - Даниил
QT_CHARTS_USE_NAMESPACE
thirdprocedure::thirdprocedure()
{
    // Ячейки по времени
    time_number = new QVector<float>();
    for (int i = 0; i < 20; i++) {
        time_number->push_back(0.0);
    }

    // Подключение к БД
    dt = new Database();

    dt->connectToDataBase("Data.db");

    QSqlQuery *qry = new QSqlQuery();

    qry->prepare("SELECT * FROM DEVICES WHERE DeviceType !=1");
    qry->exec();

    // Создание источников
    sources = new QVector<source*>();
    while(qry->next()){
        source *newSrce = new source(qry->record());
        sources->push_back(newSrce);
    }
    source_count = sources->length();

    // Ячейки по источникам
    source_number = new QVector<int>();
    for (int i = 0; i < source_count; i++) {
        source_number->push_back(0.0);
    }

    // Основной цикл
    for(int i=0;i<run_counter;i++) {
        int numb;
        int time;
        //Чтение из файла,к сожалению я не успел подключить другие модули,поэтому здесь сделан рандом.

       /* QFile file("output.txt");
        if ((file.exists())&&(file.open(QIODevice::ReadOnly))){
                QString str = file.readLine();
                QStringList lst = str.split(" ");
                    numb=lst[0].toInt();
                    time=lst[1].toInt();
                    break;
        } */
        numb = randomBetween(1,source_count);
        time = randomBetween(1,100);
        int n = source_number->at(numb-1);
        source_number->removeAt(numb-1);
        source_number->insert(numb-1, n+1);

        int j = 0;
        source* curSrc = sources->at(numb-1);
        j = qCeil(qreal(time) / qreal((curSrc->getStartTime() + (curSrc->getRepeatDuration() * curSrc->getMaxRepeatCount()))/20));
        float t = time_number->at(j);
        time_number->removeAt(j);
        time_number->insert(j, t+1);
    }
    Pk = new QVector<float>();
    QString str;
    for (int i = 0; i < source_number->length();  i++) {
        Pk->append(float(source_number->at(i)) / float(run_counter));
        str+=QString::number(Pk->last()) + "|";
    }
    data::CleanFile();
    data::printMessage(QString::number(run_counter));
    str.remove(str.length()-1, 1);
    data::printMessage(str);
    Pi = new QVector<float>();
    str = "";
    for (int i=0;i<time_number->length(); i++){
        Pi->append(time_number->at(i)/run_counter);
        str+=QString::number(Pi->last()) + "|";
    }
    str.remove(str.length()-1, 1);
    data::printMessage(str);

}
QChartView* thirdprocedure::CreateFirstDiagramm(){ //Диаграмма строящая ряд распределения времени получения
//сообщения приемником в условиях У
    QChart *chart;
    QFont font;
    font.setPixelSize(22);
    QFont lab;
    lab.setPixelSize(15);
    QPieSeries *series = new QPieSeries();
    for (int i = 0; i < time_number->length(); i++) {
        series->append(QString::number(i+1), qreal(time_number->at(i))/run_counter);
        QPieSlice *slice = series->slices().at(i);
        slice->setLabelVisible();
        slice->setExploded();
        slice->setLabelFont(lab);
        slice->setLabelBrush(QBrush(Qt::black));
        slice->setPen(QPen(Qt::black, 2));
        slice->setBrush(Qt::red);
    }

    //Добавление чарта
    chart = new QChart();

    // Добавление в чарт данных,заголовка,а также легенд.
    chart->addSeries(series);
    chart->setTitleFont(font);//Шрифт заголовка
    chart->setTitleBrush(QBrush(Qt::black));//Цвет заголовка
    chart->setTitle("First Diagramm");
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setFont(lab);
    chart->legend()->setBrush(QBrush(Qt::black));

    // Показ дисплея чарта
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;

}
QChartView* thirdprocedure::CreateSecondDiagramm(){//Диаграмма строящая вероятности получения сообщения приемником
//в условиях У от к-го источника
    QChart *chart;
    QFont font;
    font.setPixelSize(22);
    QFont lab;
    lab.setPixelSize(15);
    QPieSeries *series = new QPieSeries();
    for (int i = 0; i < Pk->length(); i++) {
        series->append(QString::number(i+1), qreal(Pk->at(i)));
        QPieSlice *slice = series->slices().at(i);
        slice->setLabelVisible();
        slice->setExploded();
        slice->setLabelFont(lab);
        slice->setLabelBrush(QBrush(Qt::black));
        slice->setPen(QPen(Qt::black, 2));
        slice->setBrush(Qt::green);
    }

    //Добавление чарта
    chart = new QChart();

    // Добавление в чарт данных,заголовка,а также легенд.
    chart->addSeries(series);
    chart->setTitleFont(font);//Шрифт заголовка
    chart->setTitleBrush(QBrush(Qt::black));//Цвет заголовка
    chart->setTitle("Second Diagramm");
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setFont(lab);
    chart->legend()->setBrush(QBrush(Qt::black));

    // Показ дисплея чарта
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;

}
