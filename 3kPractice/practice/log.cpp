#include "log.h"
#include <QDebug>
#include <QTextStream>

void Log::CleanLogFile(QString fileName)
{
    // Очистка файла
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.close();
}

void Log::printMessage(QString message, bool consolePrint, bool logFilePrint, QString fileName)
{
    // Вывод в дебаг консоли
    if (consolePrint) {
        qDebug() << message;
    }
    // Вывод в файл
    if (logFilePrint) {
        QFile file(fileName);
        if (!file.open(QIODevice::Append | QIODevice::Text))
            return;

        QTextStream out(&file);
        out << message << "\n";
        file.close();
    }
}
