#ifndef FLYEDIT_H
#define FLYEDIT_H

#pragma execution_character_set("utf-8")

#include <QtWidgets/QMainWindow>
#include "ui_flyedit.h"

#include<qsqldatabase.h>
#include<qsqltablemodel.h>
#include<qstandarditemmodel.h>

class FlyEdit : public QMainWindow
{
	Q_OBJECT

public:
	FlyEdit(QWidget *parent = 0);
	~FlyEdit();

private:
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	QSqlTableModel *model = new QSqlTableModel(this, db);
	QSqlTableModel *paraListmodel = new QSqlTableModel(this, db);
	void setupTreeView();////////至此

private:
	Ui::FlyEditClass ui;

private slots:
	void onImport();
	void onSubmit();
	void onReMod();
	void onInsRow();
	void onDeleRow();
	void paraSelect();////////////////至此
};

#endif // FLYEDIT_H
