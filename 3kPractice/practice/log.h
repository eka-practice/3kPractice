#ifndef LOG_H
#define LOG_H

#include <QString>
#include <QFile>
#include <QDebug>

class Log
{
public:
    static void printMessage(QString message, bool consolePrint = true, bool filePrint = true);
	static void CleanLogFile();

private:
};

#endif // LOG_H
