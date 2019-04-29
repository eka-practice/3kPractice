#include "log.h"
#include <QDebug>
#include <QTextStream>

void Log::CleanLogFile()
{
//    logFile = new QFile("Log.txt");
//    if (!logFile->open(QIODevice::WriteOnly)) {
//        qDebug() << "Can't open log file!" << endl;
//    }
//    else {
//        ts = new QTextStream(logFile);
//    }

    QFile file("Log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.close();
}

//Log::~Log() {
////    logFile->close();
//}

void Log::printMessage(QString message, bool consolePrint, bool logFilePrint)
{
    if (consolePrint) {
        qDebug() << message;
    }
    if (logFilePrint) {
        //logFile->write(message.toUtf8());

        QFile file("Log.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text))
            return;

        QTextStream out(&file);
        out << message << "\n";
        file.close();
    }
}
