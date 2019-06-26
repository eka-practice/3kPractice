#include "data.h"
#include <QDebug>
#include <QTextStream>
// danilagribkov@bk.ru - Даниил
void data::CleanFile(QString fileName)
{
    // Очистка файла
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.close();
}

void data::printMessage(QString message, bool consolePrint, bool dataFilePrint, QString fileName)
{
    // Вывод в дебаг консоли
    if (consolePrint) {
        qDebug() << message;
    }
    // Вывод в файл
    if (dataFilePrint) {
        QFile file(fileName);
        if (!file.open(QIODevice::Append | QIODevice::Text))
            return;

        QTextStream out(&file);
        out << message << "\n";
        file.close();
    }
}
