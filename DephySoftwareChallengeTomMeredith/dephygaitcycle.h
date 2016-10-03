#ifndef DEPHYGAITCYCLE_H
#define DEPHYGAITCYCLE_H

#include <QMainWindow>

namespace Ui {
class DephyGaitCycle;
}

class DephyGaitCycle : public QMainWindow
{
    Q_OBJECT

public:
    explicit DephyGaitCycle(QWidget *parent = 0);
    ~DephyGaitCycle();

private:
    Ui::DephyGaitCycle *ui;
};

#endif // DEPHYGAITCYCLE_H
