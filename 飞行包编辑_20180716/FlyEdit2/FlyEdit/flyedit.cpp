#include "flyedit.h"

#include<qsqldatabase.h>
#include<qmessagebox.h>
#include<qsqlerror.h>
#include<qsqltablemodel.h>
#include<qitemselectionmodel.h>
#include<QDebug>

//构造函数。类的成员变量（m_xxxx）在此函数内实例化
FlyEdit::FlyEdit(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton_Import, SIGNAL(clicked()), this, SLOT(onImport()));
	connect(ui.pushButton_Submit, SIGNAL(clicked()), this, SLOT(onSubmit()));
	connect(ui.pushButton_ReMod, SIGNAL(clicked()), this, SLOT(onReMod()));
	connect(ui.pushButton_InsRow, SIGNAL(clicked()), this, SLOT(onInsRow()));
	connect(ui.pushButton_DeleRow, SIGNAL(clicked()), this, SLOT(onDeleRow()));
	connect(ui.treeView_paraList, SIGNAL(clicked(QModelIndex)), this, SLOT(paraSelect()));////////
	m_db = QSqlDatabase::addDatabase("QMYSQL");
	m_model = new QSqlTableModel(this, m_db);
	m_paraListmodel = new QSqlTableModel(this, m_db);
	//QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	m_db.setHostName("localhost");
	m_db.setDatabaseName("test_wxb");
	m_db.setUserName("root");
	m_db.setPassword("123456");
	m_db.setPort(3306);
	bool ok = m_db.open();
	//QString err = db.lastError().databaseText();
	//QSqlTableModel *model = new QSqlTableModel(this, db);
	setupTreeView();
}

FlyEdit::~FlyEdit()
{
	m_db.close();
}

//飞行包参数列表树的初始化
void FlyEdit::setupTreeView()
{
	m_paraListmodel->clear();
	m_paraListmodel->setTable("paralist");
	m_paraListmodel->select();
	ui.treeView_paraList->setModel(m_paraListmodel);
	ui.treeView_paraList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.treeView_paraList->hideColumn(1);
	ui.treeView_paraList->show();
}

//点击treeView的某个项目，treeTable显示该参数信息
QString FlyEdit::paraSelect()////////
{
	
	QItemSelectionModel *selectionModel = ui.treeView_paraList->selectionModel();
	QModelIndex index = selectionModel->currentIndex();
	//QString text = QString("(%1,%2)").arg(index.row()).arg(index.column());//text=(rownumber,colnumber),index.row()=rownumber
	index = index.sibling(index.row(), 1);
	QMap<int, QVariant> rowMap = m_paraListmodel->itemData(index);
	//QVariant value = rowMap.value(1, QVariant());
	if(rowMap.contains(2))
	{
		QVariant value = rowMap.value(2);
		m_paraName = value.toString();
	}
	return m_paraName;
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
	if (m_paraName.isEmpty())
	{
		return;
	}
	m_model->clear();
	m_model->setTable(m_paraName);
	m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_model->select();
	//m_model->lastError();
	//m_model->setHeaderData(0, Qt::Horizontal, tr("Name"));
	//m_model->setHeaderData(1, Qt::Horizontal, tr("Salary"));
	ui.tableView_Para1->setModel(m_model);
	ui.tableView_Para1->show();

	////db.close();
}

//提交修改
void FlyEdit::onSubmit()
{
	m_model->database().transaction();//开始事务操作
	//m_model->setFilter("X=''");
	//for (int i = 0; i < m_model->rowCount(); i++)
	//{
		////m_model->setRecord(i,);
		////= model.record(i);
		////m_model->record(i)-
		////QString val_X = record->value
	//}


	//if (m_model->select())
	//{

	//	QMessageBox::information(this, "tableModel", tr("数据不能为空！"));
	//	onImport();
	//}
	//else
	//{
		if (m_model->submitAll()) // 提交所有被修改的数据到数据库中
		{
			if (m_model->database().commit())//提交//提交成功，事务将真正修改数据库数据
				QMessageBox::information(this, "tableModel", tr("数据修改成功!"));
		}
		else
		{
			m_model->database().rollback();//提交失败，事务回滚
			QMessageBox::warning(this, "tableModel", tr("数据库错误： %1").arg(m_model->lastError().text()), QMessageBox::Ok);
		}
	//}

}

//撤销未提交的修改,必须是未提交的
void FlyEdit::onReMod()
{
	m_model->revertAll();//撤销修改
}

//插入一行
void FlyEdit::onInsRow()
{
	int curRow = ui.tableView_Para1->currentIndex().row();
	if (ui.radioButton_Down->isChecked())
	{
		m_model->insertRow(curRow + 1);//在当前行下插入一行
	}
	else
	{
		m_model->insertRow(curRow);//在当前行上插入一行
	}
}

//删除选中行
void FlyEdit::onDeleRow()
{
	/*int curRow = ui.tableView_Para1->currentIndex().row();
	m_model->removeRow(curRow);
	m_model->submitAll();*/

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
			m_model->removeRow(rowToDel);
		}
	}
	int ok = QMessageBox::warning(this, "删除行！", "你确定删除所选行吗？", QMessageBox::Yes, QMessageBox::No);
	if (ok == QMessageBox::No)
	{
		m_model->revertAll();//提交，在数据库中删除该行
	}
	else
	{
		m_model->submitAll();//如果不删除，则撤销
	}

}