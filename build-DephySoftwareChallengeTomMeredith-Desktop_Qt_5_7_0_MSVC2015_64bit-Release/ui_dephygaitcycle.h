/********************************************************************************
** Form generated from reading UI file 'dephygaitcycle.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEPHYGAITCYCLE_H
#define UI_DEPHYGAITCYCLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DephyGaitCycle
{
public:
    QWidget *centralWidget;
    QFrame *line;
    QFrame *line_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DephyGaitCycle)
    {
        if (DephyGaitCycle->objectName().isEmpty())
            DephyGaitCycle->setObjectName(QStringLiteral("DephyGaitCycle"));
        DephyGaitCycle->resize(1600, 800);
        centralWidget = new QWidget(DephyGaitCycle);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(30, 370, 1571, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(20, 0, 20, 771));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        DephyGaitCycle->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DephyGaitCycle);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1600, 17));
        DephyGaitCycle->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DephyGaitCycle);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DephyGaitCycle->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DephyGaitCycle);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DephyGaitCycle->setStatusBar(statusBar);

        retranslateUi(DephyGaitCycle);

        QMetaObject::connectSlotsByName(DephyGaitCycle);
    } // setupUi

    void retranslateUi(QMainWindow *DephyGaitCycle)
    {
        DephyGaitCycle->setWindowTitle(QApplication::translate("DephyGaitCycle", "DephyGaitCycle", 0));
    } // retranslateUi

};

namespace Ui {
    class DephyGaitCycle: public Ui_DephyGaitCycle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEPHYGAITCYCLE_H
