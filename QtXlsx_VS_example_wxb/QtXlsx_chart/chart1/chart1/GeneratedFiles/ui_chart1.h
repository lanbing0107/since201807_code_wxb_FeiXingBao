/********************************************************************************
** Form generated from reading UI file 'chart1.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHART1_H
#define UI_CHART1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chart1Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *chart1Class)
    {
        if (chart1Class->objectName().isEmpty())
            chart1Class->setObjectName(QStringLiteral("chart1Class"));
        chart1Class->resize(600, 400);
        menuBar = new QMenuBar(chart1Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        chart1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(chart1Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        chart1Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(chart1Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        chart1Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(chart1Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        chart1Class->setStatusBar(statusBar);

        retranslateUi(chart1Class);

        QMetaObject::connectSlotsByName(chart1Class);
    } // setupUi

    void retranslateUi(QMainWindow *chart1Class)
    {
        chart1Class->setWindowTitle(QApplication::translate("chart1Class", "chart1", 0));
    } // retranslateUi

};

namespace Ui {
    class chart1Class: public Ui_chart1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHART1_H
