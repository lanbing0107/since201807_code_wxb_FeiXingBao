/********************************************************************************
** Form generated from reading UI file 'qtxlsx_worksheetoperations.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTXLSX_WORKSHEETOPERATIONS_H
#define UI_QTXLSX_WORKSHEETOPERATIONS_H

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

class Ui_QtXlsx_worksheetoperationsClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtXlsx_worksheetoperationsClass)
    {
        if (QtXlsx_worksheetoperationsClass->objectName().isEmpty())
            QtXlsx_worksheetoperationsClass->setObjectName(QStringLiteral("QtXlsx_worksheetoperationsClass"));
        QtXlsx_worksheetoperationsClass->resize(600, 400);
        menuBar = new QMenuBar(QtXlsx_worksheetoperationsClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        QtXlsx_worksheetoperationsClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtXlsx_worksheetoperationsClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtXlsx_worksheetoperationsClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtXlsx_worksheetoperationsClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QtXlsx_worksheetoperationsClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtXlsx_worksheetoperationsClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtXlsx_worksheetoperationsClass->setStatusBar(statusBar);

        retranslateUi(QtXlsx_worksheetoperationsClass);

        QMetaObject::connectSlotsByName(QtXlsx_worksheetoperationsClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtXlsx_worksheetoperationsClass)
    {
        QtXlsx_worksheetoperationsClass->setWindowTitle(QApplication::translate("QtXlsx_worksheetoperationsClass", "QtXlsx_worksheetoperations", 0));
    } // retranslateUi

};

namespace Ui {
    class QtXlsx_worksheetoperationsClass: public Ui_QtXlsx_worksheetoperationsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTXLSX_WORKSHEETOPERATIONS_H
