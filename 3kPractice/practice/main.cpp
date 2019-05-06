#include "mainwindow.h"
#include <QCoreApplication>
#include "world.h"
#include "locale.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Rus");

    QCoreApplication a(argc, argv);

    World *wrld = new World();
    wrld->modelStart();

    return a.exec();
}
