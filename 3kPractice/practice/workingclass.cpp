#include "workingclass.h"
#include "QRandomGenerator"

WorkingClass::WorkingClass()
{
    // Чтение базы
    db = new Database();

    db->connectToDataBase("Data.db");

    QSqlQuery *qry = new QSqlQuery();
    qry->prepare("SELECT * FROM Devices WHERE DeviceType != 1");
    qry->exec();

    sources = new QVector<Source*>();

    while (qry->next()) {
        sources->append(new Source(qry->record()));
    }

    mReceivePeriodicity = new QVector<QVector<float>*>();
    timeRows = new QVector<QVector<float>*>();

    // Чтение протокола txt
    QFile file("input.txt");
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        // Число прогонов
        QString str = file.readLine();
        maxX = str.toInt();

        sequences = new QVector<QVector<int>*>();
        n0 = new QVector<QVector<int>*>();
        while (!file.atEnd()) {
            str = file.readLine();
            QStringList lst = str.split("|");
            QVector<int>* vec = new QVector<int>();
            for (int i = 0; i < lst.length(); i++) {
                vec->append(lst.at(i).toInt());
            }
            sequences->append(vec);

            str = file.readLine();
            lst = str.split("|");
            vec = new QVector<int>();
            for (int i = 0; i < lst.length(); i++) {
                vec->append(lst.at(i).toInt());
            }
            n0->append(vec);
        }

        file.close();
    }

    // Основная часть работы
    for (int i = 0; i < sequences->length(); i++) { // Цикл по всем вариантам наборов радиоданных
        for (X = 0; X < maxX; X++) { // Цикл по прогонам
            // Разыгрываем вероятности поражения источника
            brokenTime = new QVector<int>();
            for (int k = 0; k < sources->length(); k++) {
                Source* src = sources->at(k);
                if (QRandomGenerator::global()->generateDouble() < double(src->getInfluenceProbability())) {
                    brokenTime->push_back(src->getInfluenceTime());
                }
                else {
                    brokenTime->push_back(src->getStartTime() + src->getRepeatDuration() * src->getMaxRepeatCount());
                }
            }

            // Запуск программы Даниила
            // ...

            // Получение данных
            // Чтение протокола из txt-файла
            QFile protocol("proto.txt");
            if (protocol.exists() && protocol.open(QIODevice::ReadOnly)) {
                // Ряд распределения времени получения сообщения
                QVector<float>* timeRow = new QVector<float>();
                QString str = protocol.readLine();
                QStringList lst = str.split("|");
                for (int j = 0; j < lst.length(); j++) {
                    timeRow->append(lst.at(j).toFloat());
                }
                timeRows->append(timeRow);
                // Частоты получения сообщения
                QVector<float>* mReceivePeriodicityRow = new QVector<float>();
                str = protocol.readLine();
                lst = str.split("|");
                for (int j = 0; j < lst.length(); j++) {
                    mReceivePeriodicityRow->append(lst.at(j).toFloat());
                }
                mReceivePeriodicity->append(mReceivePeriodicityRow);
                protocol.close();
            }
        }
    }
    // Сравнение по Парето

    QVector<QVector<float>*>* pareto = new QVector<QVector<float>*>();

    for (int i = 0; i < sources->length(); i++) {
        // Находим максимальную вероятность
        float max = 0;
        for (int j = 0; j < 20; j++) {
            if (timeRows->at(j)->at(i) > max) {
                max = timeRows->at(j)->at(i);
            }
        }
        for (int j = 19; j >= 0; j++) {
            if (timeRows->at(j)->at(i) == max) {
                pareto->append(timeRows->at(j));
            }
        }
    }

    for (int i = 0; i < pareto->length(); i++) {
        for (int j = 0; j < pareto->at(i)->length(); j++) {
            qDebug() << pareto->at(i)->at(j) << " ";
        }
    }
}

void WorkingClass::modelStart()
{
    started = true;
}
