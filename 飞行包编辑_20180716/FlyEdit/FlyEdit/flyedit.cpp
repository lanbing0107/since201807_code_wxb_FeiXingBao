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
	//////至此connect(ui.treeView_paraList, SIGNAL(currentChanged()))

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

//飞行包参数列表树的初始化
void FlyEdit::setupTreeView()
{
	paraListmodel->clear();
	paraListmodel->setTable("paralist");
	paraListmodel->select();
	ui.treeView_paraList->setModel(paraListmodel);
	ui.treeView_paraList->show();
}

//导入某一个MySQL表格
void FlyEdit::onImport()
{
	////bool ok = db.open();
	/*if (db.open())
	{
	QMessageBox::warning(NULL, QStringLiteral("提示"), "open ok", QMessageBox::Yes);
	}
	else
	{
	QMessageBox::warning(NULL, QStringLiteral("提示"), "open failed", QMessageBox::Yes);
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

//提交修改
void FlyEdit::onSubmit()
{
	model->database().transaction();//开始事务操作
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

	//	QMessageBox::information(this, "tableModel", tr("数据不能为空！"));
	//	onImport();
	//}
	//else
	//{
		if (model->submitAll()) // 提交所有被修改的数据到数据库中
		{
			if (model->database().commit())//提交//提交成功，事务将真正修改数据库数据
				QMessageBox::information(this, "tableModel", tr("数据修改成功!"));
		}
		else
		{
			model->database().rollback();//提交失败，事务回滚
			QMessageBox::warning(this, "tableModel", tr("数据库错误： %1").arg(model->lastError().text()), QMessageBox::Ok);
		}
	//}

}

//撤销未提交的修改,必须是未提交的
void FlyEdit::onReMod()
{
	model->revertAll();//撤销修改
}

//插入一行
void FlyEdit::onInsRow()
{
	int curRow = ui.tableView_Para1->currentIndex().row();
	if (ui.radioButton_Down->isChecked())
	{
		model->insertRow(curRow + 1);//在当前行下插入一行
	}
	else
	{
		model->insertRow(curRow);//在当前行上插入一行
	}
}

//删除选中行
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
		if (rowMapIterator.hasPrevious())//用while?
		{
			rowMapIterator.previous();
			rowToDel = rowMapIterator.key();
			model->removeRow(rowToDel);
		}
	}
	int ok = QMessageBox::warning(this, "删除行！", "你确定删除所选行吗？", QMessageBox::Yes, QMessageBox::No);
	if (ok == QMessageBox::No)
	{
		model->revertAll();//提交，在数据库中删除该行
	}
	else
	{
		model->submitAll();//如果不删除，则撤销
	}

}