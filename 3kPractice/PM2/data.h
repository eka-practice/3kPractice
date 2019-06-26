#ifndef DATA_H
#define DATA_H


#include <QString>
#include <QFile>
#include <QDebug>

// danilagribkov@bk.ru - Даниил
// Класс для вывода из программы в текстовый файл.

class data
{
public:
    /// Вывод сообщения
    /// message - сообщение
    /// consolePrint - выводить ли в консоль
    /// filePrint - выводить ли в файл
    static void printMessage(QString message, bool consolePrint = true, bool filePrint = true, QString fileName = "data.txt");
    /// Очистка файла
    static void CleanFile(QString fileName = "data.txt");
};
#endif // DATA_H
