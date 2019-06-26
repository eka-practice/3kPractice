#include "secondwidget.h"
#include "ui_secondwidget.h"
#include "secondprocedure.h"
secondwidget::secondwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::secondwidget)
{
    ui->setupUi(this);
    secondprocedure *proc = new secondprocedure();

    //ui->secondprocedurelayout->addWidget(proc->CreateFirstDiagramm());
   // ui->secondprocedurelayout->addWidget(proc->CreateSecondDiagramm());
   // ui->secondprocedurelayout->addWidget(proc->CreateThirdDiagramm());
   // ui->secondprocedurelayout->addWidget(proc->CreateFourthDiagramm());
}

secondwidget::~secondwidget()
{
    delete ui;
}
