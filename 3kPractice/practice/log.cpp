#include "log.h"
#include <QDebug>
#include <QTextStream>

void Log::CleanLogFile()
{
    // Очистка файла
    QFile file("Log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.close();
}

void Log::printMessage(QString message, bool consolePrint, bool logFilePrint)
{
    // Вывод в дебаг консоли
    if (consolePrint) {
        qDebug() << message;
    }
    // Вывод в файл
    if (logFilePrint) {
        QFile file("Log.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text))
            return;

        QTextStream out(&file);
        out << message << "\n";
        file.close();
    }
}
