/********************************************************************************
** Form generated from reading UI file 'qtxlsx_extractdata.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTXLSX_EXTRACTDATA_H
#define UI_QTXLSX_EXTRACTDATA_H

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

class Ui_QtXlsx_extractdataClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtXlsx_extractdataClass)
    {
        if (QtXlsx_extractdataClass->objectName().isEmpty())
            QtXlsx_extractdataClass->setObjectName(QStringLiteral("QtXlsx_extractdataClass"));
        QtXlsx_extractdataClass->resize(600, 400);
        menuBar = new QMenuBar(QtXlsx_extractdataClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        QtXlsx_extractdataClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtXlsx_extractdataClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtXlsx_extractdataClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtXlsx_extractdataClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QtXlsx_extractdataClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtXlsx_extractdataClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtXlsx_extractdataClass->setStatusBar(statusBar);

        retranslateUi(QtXlsx_extractdataClass);

        QMetaObject::connectSlotsByName(QtXlsx_extractdataClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtXlsx_extractdataClass)
    {
        QtXlsx_extractdataClass->setWindowTitle(QApplication::translate("QtXlsx_extractdataClass", "QtXlsx_extractdata", 0));
    } // retranslateUi

};

namespace Ui {
    class QtXlsx_extractdataClass: public Ui_QtXlsx_extractdataClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTXLSX_EXTRACTDATA_H
