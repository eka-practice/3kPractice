#include "firstprocedure.h"
#include <QApplication>
#include <mainwindow.h>
#include "secondprocedure.h"
#include "firstwidget.h"
#include "secondwidget.h"
#include "thirdwidget.h"
// danilagribkov@bk.ru - Даниил
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FirstWidget *w = new FirstWidget(); //Запуск 1 процедуры с отрисовкой диаграмм
    w->show();

    //secondprocedure *b = new secondprocedure; //Идет запуск только программы,так как не успел доделать диаграммы

    //thirdwidget *c = new thirdwidget(); //Запуск 3 процедуры с отрисовкой диаграмм
    //c->show();
    return a.exec();
}
