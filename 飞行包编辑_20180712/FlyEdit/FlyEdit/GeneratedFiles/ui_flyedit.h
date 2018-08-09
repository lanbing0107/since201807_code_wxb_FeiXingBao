/********************************************************************************
** Form generated from reading UI file 'flyedit.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLYEDIT_H
#define UI_FLYEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FlyEditClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_Import;
    QTableView *tableView_Para1;
    QPushButton *pushButton_Submit;
    QPushButton *pushButton_ReMod;
    QPushButton *pushButton_InsRow;
    QGroupBox *groupBox;
    QRadioButton *radioButton_Down;
    QRadioButton *radioButton_Up;
    QPushButton *pushButton_DeleRow;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FlyEditClass)
    {
        if (FlyEditClass->objectName().isEmpty())
            FlyEditClass->setObjectName(QStringLiteral("FlyEditClass"));
        FlyEditClass->resize(925, 746);
        centralWidget = new QWidget(FlyEditClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_Import = new QPushButton(centralWidget);
        pushButton_Import->setObjectName(QStringLiteral("pushButton_Import"));
        pushButton_Import->setGeometry(QRect(70, 520, 93, 28));
        tableView_Para1 = new QTableView(centralWidget);
        tableView_Para1->setObjectName(QStringLiteral("tableView_Para1"));
        tableView_Para1->setGeometry(QRect(70, 30, 381, 451));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableView_Para1->sizePolicy().hasHeightForWidth());
        tableView_Para1->setSizePolicy(sizePolicy);
        tableView_Para1->setDragEnabled(false);
        pushButton_Submit = new QPushButton(centralWidget);
        pushButton_Submit->setObjectName(QStringLiteral("pushButton_Submit"));
        pushButton_Submit->setGeometry(QRect(500, 520, 93, 28));
        pushButton_ReMod = new QPushButton(centralWidget);
        pushButton_ReMod->setObjectName(QStringLiteral("pushButton_ReMod"));
        pushButton_ReMod->setGeometry(QRect(390, 520, 93, 28));
        pushButton_InsRow = new QPushButton(centralWidget);
        pushButton_InsRow->setObjectName(QStringLiteral("pushButton_InsRow"));
        pushButton_InsRow->setGeometry(QRect(290, 520, 71, 28));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(180, 510, 101, 51));
        radioButton_Down = new QRadioButton(groupBox);
        radioButton_Down->setObjectName(QStringLiteral("radioButton_Down"));
        radioButton_Down->setGeometry(QRect(10, 6, 81, 19));
        radioButton_Down->setChecked(true);
        radioButton_Up = new QRadioButton(groupBox);
        radioButton_Up->setObjectName(QStringLiteral("radioButton_Up"));
        radioButton_Up->setGeometry(QRect(10, 30, 81, 19));
        pushButton_DeleRow = new QPushButton(centralWidget);
        pushButton_DeleRow->setObjectName(QStringLiteral("pushButton_DeleRow"));
        pushButton_DeleRow->setGeometry(QRect(620, 520, 81, 28));
        FlyEditClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FlyEditClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 925, 26));
        FlyEditClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FlyEditClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        FlyEditClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FlyEditClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FlyEditClass->setStatusBar(statusBar);

        retranslateUi(FlyEditClass);

        QMetaObject::connectSlotsByName(FlyEditClass);
    } // setupUi

    void retranslateUi(QMainWindow *FlyEditClass)
    {
        FlyEditClass->setWindowTitle(QApplication::translate("FlyEditClass", "FlyEdit", nullptr));
        pushButton_Import->setText(QApplication::translate("FlyEditClass", "\345\257\274\345\205\245", nullptr));
        pushButton_Submit->setText(QApplication::translate("FlyEditClass", "\346\217\220\344\272\244\344\277\256\346\224\271", nullptr));
        pushButton_ReMod->setText(QApplication::translate("FlyEditClass", "\346\222\244\351\224\200\344\277\256\346\224\271", nullptr));
        pushButton_InsRow->setText(QApplication::translate("FlyEditClass", "\346\217\222\345\205\245\350\241\214", nullptr));
        groupBox->setTitle(QString());
        radioButton_Down->setText(QApplication::translate("FlyEditClass", "\345\275\223\345\211\215\350\241\214\344\270\213", nullptr));
        radioButton_Up->setText(QApplication::translate("FlyEditClass", "\345\275\223\345\211\215\350\241\214\344\270\212", nullptr));
        pushButton_DeleRow->setText(QApplication::translate("FlyEditClass", "\345\210\240\351\231\244\351\200\211\344\270\255\350\241\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FlyEditClass: public Ui_FlyEditClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLYEDIT_H
