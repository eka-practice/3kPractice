#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "firstprocedure.h"
#include <QWidget>
// danilagribkov@bk.ru - Даниил

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
