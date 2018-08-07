#include "flyedit.h"

#include<qsqldatabase.h>
#include<qmessagebox.h>
#include<qsqlerror.h>
#include<qsqltablemodel.h>
#include<qitemselectionmodel.h>

FlyEdit::FlyEdit(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton_Import, SIGNAL(clicked()), this, SLOT(onImport()));
	connect(ui.pushButton_Submit, SIGNAL(clicked()), this, SLOT(onSubmit()));
	connect(ui.pushButton_ReMod, SIGNAL(clicked()), this, SLOT(onReMod()));
	connect(ui.pushButton_InsRow, SIGNAL(clicked()), this, SLOT(onInsRow()));
	connect(ui.pushButton_DeleRow, SIGNAL(clicked()), this, SLOT(onDeleRow()));
	//////����connect(ui.treeView_paraList, SIGNAL(currentChanged()))

	//QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setDatabaseName("test_wxb");
	db.setUserName("root");
	db.setPassword("123456");
	db.setPort(3306);
	bool ok = db.open();
	//QString err = db.lastError().databaseText();
	//QSqlTableModel *model = new QSqlTableModel(this, db);
}

FlyEdit::~FlyEdit()
{
	db.close();
}

//���а������б����ĳ�ʼ��
void FlyEdit::setupTreeView()
{
	paraListmodel->clear();
	paraListmodel->setTable("paralist");
	paraListmodel->select();
	ui.treeView_paraList->setModel(paraListmodel);
	ui.treeView_paraList->show();
}

//����ĳһ��MySQL���
void FlyEdit::onImport()
{
	////bool ok = db.open();
	/*if (db.open())
	{
	QMessageBox::warning(NULL, QStringLiteral("��ʾ"), "open ok", QMessageBox::Yes);
	}
	else
	{
	QMessageBox::warning(NULL, QStringLiteral("��ʾ"), "open failed", QMessageBox::Yes);
	QString err = db.lastError().databaseText();
	}
	db.close();*/

	////QSqlTableModel *model = new QSqlTableModel(this, db);
	model->clear();
	model->setTable("1x");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->select();
	//model->setHeaderData(0, Qt::Horizontal, tr("Name"));
	//model->setHeaderData(1, Qt::Horizontal, tr("Salary"));
	ui.tableView_Para1->setModel(model);
	ui.tableView_Para1->show();

	////db.close();
}

//�ύ�޸�
void FlyEdit::onSubmit()
{
	model->database().transaction();//��ʼ�������
	//model->setFilter("X=''");
	//for (int i = 0; i < model->rowCount(); i++)
	//{
		////model->setRecord(i,);
		////= model.record(i);
		////model->record(i)-
		////QString val_X = record->value
	//}


	//if (model->select())
	//{

	//	QMessageBox::information(this, "tableModel", tr("���ݲ���Ϊ�գ�"));
	//	onImport();
	//}
	//else
	//{
		if (model->submitAll()) // �ύ���б��޸ĵ����ݵ����ݿ���
		{
			if (model->database().commit())//�ύ//�ύ�ɹ������������޸����ݿ�����
				QMessageBox::information(this, "tableModel", tr("�����޸ĳɹ�!"));
		}
		else
		{
			model->database().rollback();//�ύʧ�ܣ�����ع�
			QMessageBox::warning(this, "tableModel", tr("���ݿ���� %1").arg(model->lastError().text()), QMessageBox::Ok);
		}
	//}

}

//����δ�ύ���޸�,������δ�ύ��
void FlyEdit::onReMod()
{
	model->revertAll();//�����޸�
}

//����һ��
void FlyEdit::onInsRow()
{
	int curRow = ui.tableView_Para1->currentIndex().row();
	if (ui.radioButton_Down->isChecked())
	{
		model->insertRow(curRow + 1);//�ڵ�ǰ���²���һ��
	}
	else
	{
		model->insertRow(curRow);//�ڵ�ǰ���ϲ���һ��
	}
}

//ɾ��ѡ����
void FlyEdit::onDeleRow()
{
	/*int curRow = ui.tableView_Para1->currentIndex().row();
	model->removeRow(curRow);
	model->submitAll();*/

	QItemSelectionModel *selections = ui.tableView_Para1->selectionModel();
	QModelIndexList selected = selections->selectedIndexes();

	foreach(QModelIndex index, selected)
	{
		QMap<int, int> rowMap;
		rowMap.insert(index.row(), 0);

		int rowToDel;
		QMapIterator<int, int> rowMapIterator(rowMap);
		rowMapIterator.toBack();
		if (rowMapIterator.hasPrevious())//��while?
		{
			rowMapIterator.previous();
			rowToDel = rowMapIterator.key();
			model->removeRow(rowToDel);
		}
	}
	int ok = QMessageBox::warning(this, "ɾ���У�", "��ȷ��ɾ����ѡ����", QMessageBox::Yes, QMessageBox::No);
	if (ok == QMessageBox::No)
	{
		model->revertAll();//�ύ�������ݿ���ɾ������
	}
	else
	{
		model->submitAll();//�����ɾ��������
	}

}