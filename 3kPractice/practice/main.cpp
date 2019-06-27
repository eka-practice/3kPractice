#include <QCoreApplication>
#include "workingclass.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    WorkingClass* wc = new WorkingClass();

    return a.exec();
}
