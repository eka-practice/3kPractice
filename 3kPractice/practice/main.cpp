#include "mainwindow.h"
#include <QCoreApplication>
#include "world.h"
#include "locale.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Rus");

    QCoreApplication a(argc, argv);

    QFile file("info.txt"); // Если есть файл входных данных Дмитрия
    if (file.exists()) {
        file.open(QIODevice::ReadOnly);
        QStringList *IDs = new QStringList();
        QString receiverID = file.readLine();
        IDs->append(QString(file.readLine()).remove("\r\n").split('|'));
        IDs->append(receiverID.remove("\r\n"));
        int time = file.readLine().toInt();
        QString radioStr = file.readLine();
        if (radioStr.split('|').length() >= 1) {
            QStringList radioLst = radioStr.split('|');
            QVector<int> *radioNum = new QVector<int>();
            for (int i = 0; i < radioLst.length(); i++) {
                radioNum->push_back(radioLst.at(i).toUInt());
            }
            World *world = new World(IDs, radioNum, time);
            world->modelStart();
        }
    }
    else {
        World *world = new World();
        world->modelStart();
    }

    return a.exec();
}
