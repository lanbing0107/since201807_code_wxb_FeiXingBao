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

//signals:
//	void activated(QModelIndex index);

private:
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	QSqlTableModel *model = new QSqlTableModel(this, db);
	QSqlTableModel *paraListmodel = new QSqlTableModel(this, db);
	void setupTreeView();////////
	QString paraName;/////////

private:
	Ui::FlyEditClass ui;

private slots:
	void onImport();
	void onSubmit();
	void onReMod();
	void onInsRow();
	void onDeleRow();
	QString paraSelect();////////////////жа╢к
};

#endif // FLYEDIT_H
