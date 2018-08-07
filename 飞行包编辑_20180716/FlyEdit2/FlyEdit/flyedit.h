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
	FlyEdit(QWidget *parent = 0);//���캯��
	~FlyEdit();//��������

//signals:
//	void activated(QModelIndex index);

private:
	QSqlDatabase m_db;//m_xxxx����ĳ�Ա������������.h�ļ��ж����Ա������.cpp�ļ����캯����ʵ������Ա����
	QSqlTableModel *m_model;
	QSqlTableModel *m_paraListmodel;
	void setupTreeView();////////
	QString m_paraName;/////////

private:
	Ui::FlyEditClass ui;

private slots:
	void onImport();
	void onSubmit();
	void onReMod();
	void onInsRow();
	void onDeleRow();
	QString paraSelect();////////////////����
};

#endif // FLYEDIT_H
