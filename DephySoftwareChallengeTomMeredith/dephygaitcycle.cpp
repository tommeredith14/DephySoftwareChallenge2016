#include "dephygaitcycle.h"
#include "ui_dephygaitcycle.h"

DephyGaitCycle::DephyGaitCycle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DephyGaitCycle)
{
    ui->setupUi(this);
}

DephyGaitCycle::~DephyGaitCycle()
{
    delete ui;
}
