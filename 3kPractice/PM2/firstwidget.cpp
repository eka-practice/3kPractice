#include "firstwidget.h"
#include "ui_firstwidget.h"
#include "firstprocedure.h"
//Создание диаграмм
FirstWidget::FirstWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FirstWidget)
{
    ui->setupUi(this);

    Firstprocedure *proc = new Firstprocedure();

    ui->horizontalLayout->addWidget(proc->CreateFirstDiagramm());
    ui->horizontalLayout->addWidget(proc->CreateSecondDiagramm());
}

FirstWidget::~FirstWidget()
{
    delete ui;
}
