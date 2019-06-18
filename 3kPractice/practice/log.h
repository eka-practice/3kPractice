#ifndef LOG_H
#define LOG_H

#include <QString>
#include <QFile>
#include <QDebug>

// lor1113@yandex.ru - Андрей
// Класс логирования событий в журнал.

class Log
{
public:
    /// Вывод сообщения
    /// message - сообщение
    /// consolePrint - выводить ли в консоль
    /// filePrint - выводить ли в файл
    static void printMessage(QString message, bool consolePrint = true, bool filePrint = true, QString fileName = "Log.txt");
    /// Очистка файла
    static void CleanLogFile(QString fileName = "Log.txt");
};

#endif // LOG_H
