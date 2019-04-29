#include "mainwindow.h"
#include <QCoreApplication>
#include "world.h"
#include "locale.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Rus");
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();

    QCoreApplication a(argc, argv);

    World *wrld = new World();
    wrld->modelStart();

    return a.exec();
}
