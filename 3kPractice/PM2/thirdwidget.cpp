#include "thirdwidget.h"
#include "ui_thirdwidget.h"
#include "thirdprocedure.h"
thirdwidget::thirdwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::thirdwidget)
{
    ui->setupUi(this);
    thirdprocedure *proc = new thirdprocedure();

    ui->thirdprocedurelayout->addWidget(proc->CreateFirstDiagramm());
    ui->thirdprocedurelayout->addWidget(proc->CreateSecondDiagramm());
}

thirdwidget::~thirdwidget()
{
    delete ui;
}
