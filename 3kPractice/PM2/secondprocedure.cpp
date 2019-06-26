#include "secondprocedure.h"
#include "source.h"
#include <QtMath>
#include "data.h"
// danilagribkov@bk.ru - Даниил
QT_CHARTS_USE_NAMESPACE
secondprocedure::secondprocedure()
{
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

    // Ячейки по времени
    time_number = new QVector<QVector<float>*>();
    for (int i = 0; i < 20; i++) {
        QVector<float> *vec = new QVector<float>();
        for (int j = 0; j < source_count; j++){
            vec->push_back(0.0);
        }
        time_number->push_back(vec);
    }

    // Ячейки по источникам
    source_number = new QVector<QVector<int>*>();
    for (int i = 0; i < source_count; i++) {
        QVector<int> *vec = new QVector<int>();
        for(int j=0;j < source_count; j++){
            vec->push_back(0.0);
        }
        source_number->push_back(vec);
    }

    // Основной цикл
    for(int i=0;i<run_counter;i++) {
        int numb;
        int rads;
        int time;
        //Чтение из файла,к сожалению я не успел подключить другие модули,поэтому здесь сделан рандом.

       /* QFile file("Log.txt");
        if ((file.exists())&&(file.open(QIODevice::ReadOnly))){
            while(!file.atEnd()){
                QString str = file.readLine();
                QStringList lst = str.split(" ");
                if(lst[0]=="ПСО"){
                    numb=lst[2].toInt();
                    time=lst[3].toInt();
                    break;
                }
                else if(lst[0]=="НПС"){
                    qDebug() << "Сообщение не получено\n";
                } // Фиксируется событие не получения сообщения
            }
        }
        */
        numb = randomBetween(1,source_count);
        rads = randomBetween(1,source_count);
        time = randomBetween(1,100);
        source* curSrc = sources->at(numb-1);

        int j = qCeil(qreal(time) / qreal((curSrc->getStartTime() + (curSrc->getRepeatDuration() * curSrc->getMaxRepeatCount()))/20));
        QVector<float> *t = time_number->at(j);
        int n = t->at(numb-1) + 1;
        t->removeAt(numb-1);
        t->insert(numb-1, n);
        time_number->removeAt(j);
        time_number->insert(j, t);

        QVector<int>* vec = source_number->at(rads-1);
        int f = vec->at(numb-1) + 1;
        vec->removeAt(numb-1);
        vec->insert(numb-1, f);
        source_number->removeAt(rads-1);
        source_number->insert(rads-1, vec);
    }
    data::CleanFile();
    data::printMessage(QString::number(run_counter));
    Pk = new QVector<QVector<float>*>();
    QString str;
    for (int i = 0; i < source_number->length();  i++) {
        QVector<float> *vec = new QVector<float>();
        for (int j = 0; j < source_number->at(i)->length();  j++) {
            vec->append(float(source_number->at(i)->at(j)) /float(run_counter));
            str+=QString::number(vec->last()) + "|";
        }
        Pk->append(vec);
        str.remove(str.length()-1,1);
        data::printMessage(str);
        str="";
    }
    data::printMessage("");
    Pi = new QVector<QVector<float>*>();
    str = "";
    for (int i = 0; i < time_number->length();  i++) {
        QVector<float> *vec = new QVector<float>();
        for (int j = 0; j < time_number->at(i)->length();  j++) {
            vec->append(time_number->at(i)->at(j) / run_counter);
            str+=QString::number(vec->last()) + "|";
        }
        Pi->append(vec);
        str.remove(str.length()-1,1);
        data::printMessage(str);
        str="";
    }

}
//Диаграммы к второму алгоритму не успел доделать.

/*QChartView* secondprocedure::CreateFirstDiagramm(){ //Диаграмма строящая ряд распределения времени получения
//сообщения для получателей
    QChart *chart;
    QFont font;
    font.setPixelSize(22);
    QFont lab;
    lab.setPixelSize(15);
    QPieSeries *series = new QPieSeries();
    for (int i = 0; i < time_number->length(); i++) {
        series->append(QString::number(i+1), (time_number->at(i))/run_counter);
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
QChartView* secondprocedure::CreateSecondDiagramm(){//Диаграмма строящая вероятности получения сообщения для каждой
//части получателей
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
*/
