/********************************************************************************
** Form generated from reading UI file 'ssw.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SSW_H
#define UI_SSW_H

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

class Ui_sswClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *sswClass)
    {
        if (sswClass->objectName().isEmpty())
            sswClass->setObjectName(QStringLiteral("sswClass"));
        sswClass->resize(600, 400);
        menuBar = new QMenuBar(sswClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        sswClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(sswClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        sswClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(sswClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sswClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(sswClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        sswClass->setStatusBar(statusBar);

        retranslateUi(sswClass);

        QMetaObject::connectSlotsByName(sswClass);
    } // setupUi

    void retranslateUi(QMainWindow *sswClass)
    {
        sswClass->setWindowTitle(QApplication::translate("sswClass", "ssw", 0));
    } // retranslateUi

};

namespace Ui {
    class sswClass: public Ui_sswClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SSW_H
