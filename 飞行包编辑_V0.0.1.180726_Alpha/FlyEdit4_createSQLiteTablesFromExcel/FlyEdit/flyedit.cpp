#include "flyedit.h"

#include<qsqldatabase.h>
#include<qmessagebox.h>
#include<qsqlerror.h>
#include<qsqltablemodel.h>
#include<qitemselectionmodel.h>
#include<qfiledialog.h>
#include<QtXlsx\xlsxdocument.h>
#include<qsqlquery.h>
#include <qdebug.h>
#include<qsqlrecord.h>

//构造函数（实现初始化）。类的成员变量（m_xxxx）在此函数内实例化
FlyEdit::FlyEdit(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	////connect(ui.pushButton_Import, SIGNAL(clicked()), this, SLOT(onImport()));
	connect(ui.pushButton_Submit, SIGNAL(clicked()), this, SLOT(onSubmit()));
	connect(ui.pushButton_ReMod, SIGNAL(clicked()), this, SLOT(onReMod()));
	connect(ui.pushButton_InsRow, SIGNAL(clicked()), this, SLOT(onInsRow()));
	connect(ui.pushButton_DeleRow, SIGNAL(clicked()), this, SLOT(onDeleRow()));
	connect(ui.treeView_paraList, SIGNAL(clicked(QModelIndex)), this, SLOT(paraSelectAndShow()));////////
	connect(ui.pushButton_ImportExcel, SIGNAL(clicked()), this, SLOT(onImportExcel()));
	connect(ui.pushButton_ExportToExcel, SIGNAL(clicked()), this, SLOT(onExportToExcel()));
	/*m_db = QSqlDatabase::addDatabase("QMYSQL");
	m_model = new QSqlTableModel(this, m_db);
	m_paraListmodel = new QSqlTableModel(this, m_db);
	//QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	m_db.setHostName("localhost");
	m_db.setDatabaseName("test_wxb");
	m_db.setUserName("root");
	m_db.setPassword("123456");
	m_db.setPort(3306);
	bool ok = m_db.open();*/  //ok
	//QString err = db.lastError().databaseText();
	//QSqlTableModel *model = new QSqlTableModel(this, db);

	m_db = QSqlDatabase::addDatabase("QSQLITE");
	m_model = new QSqlTableModel(this, m_db);
	m_paraListmodel = new QSqlTableModel(this, m_db);
	m_path = QDir::currentPath();//可以用QDir::setCurrent(const QString &path)设置工作目录
	m_dataBasePathName = m_path.append("/test_flyEdit.db");
	m_db.setDatabaseName(m_dataBasePathName);
	bool ok = m_db.open();
	
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
	//QSqlQuery query(m_db);
	//QString sqlCmdSelect = QString("SELECT name FROM sqlite_master WHERE type='table' ORDER BY name");
	//query.exec(sqlCmdSelect);
	////error = query.lastError().databaseText();
	//QString tableName1;
	//if(query.next())
	//{
	//	tableName1 = query.value(0).toString();
	//}
	//else
	//{
	//	return;
	//}
	m_paraListmodel->setTable("paralist");//总表名总是paralist，这个是定死的
	m_paraListmodel->select();
	ui.treeView_paraList->setModel(m_paraListmodel);
	ui.treeView_paraList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.treeView_paraList->hideColumn(1);
	ui.treeView_paraList->resizeColumnToContents(0);//根据内容自适应列宽
	ui.treeView_paraList->show();
}

//从Excel导入所有参数数据（包含参数总表和每个参数的sheet）
void FlyEdit::onImportExcel()
{
	QString excelFileName = QFileDialog::getOpenFileName(this, tr("选择Excel文件"), m_path, tr("Excel 工作簿(*.xlsx);;Excel 97-2003 工作簿(*.xls)"));
	if (excelFileName == "")
	{
		return;
	}
	//-------------------------------------------------------//
	//if判断文件格式和内容（设置一个int类型标记量），记录是否正确打开且符合格式内容，否则提示错误，treeView中不显示

	//------------------------删除数据库原有表-----------------------------//
	QSqlQuery query(m_db);
	QString sqlCmdSelectOldTable = QString("SELECT name FROM sqlite_master WHERE type='table' ORDER BY name");
	query.exec(sqlCmdSelectOldTable);
	//error = query.lastError().databaseText();
	QStringList oldTableNames;
	while (query.next())
	{
		QString oldTableName = query.value(0).toString();
		oldTableNames.append(oldTableName);
		
	}
	int oldTableNumber = oldTableNames.size();
	QSqlQuery query2(m_db);
	for (int i = 0; i < oldTableNumber; ++i)
	{
		QString oldTableName = oldTableNames.value(i);
		QString sqlCmdDeleteOldTable = QString("DROP TABLE %1").arg(oldTableName);
		query2.exec(sqlCmdDeleteOldTable);
		QString error = query2.lastError().databaseText();
	}
	
	//---------------------从Excel读sheet，创建数据库表--------------------//



	//------------------------将Excel内容写入数据库------------------------//



	QXlsx::Document xlsx(excelFileName);
	QStringList sheetNames = xlsx.sheetNames();//Excel文件各sheet表名
	int sheetNumber = sheetNames.size();//sheet个数，从0开始
	QString error;
	for (int i = 0; i < sheetNumber; ++i)
	{
		QString shName = sheetNames.value(i);//QString shName2 = sheetnames.at(i);
		xlsx.selectSheet(shName);
		QXlsx::CellRange range = xlsx.dimension();
		int rowCounts = range.lastRow();//获取打开文件的最后一行（注意，如果最后一行有空格也为有效行）
		int colCounts = range.lastColumn();//获取打开文件的最后一列
		QSqlQuery query(m_db);






		for (int ir = 2; ir < rowCounts + 1; ir++)
		{
			if (ir == 2)//Excel要覆盖数据库内容，所以先删除表内原有数据
			{
				QString sqlCmdDelete = QString("delete from %1").arg(shName);
				query.exec(sqlCmdDelete);
				error = query.lastError().databaseText();
				//需判断错误情况，并给出相应提示信息	
			}
			QString tempC1 = xlsx.read(ir, 1).toString();
			QString tempC2 = xlsx.read(ir, 2).toString();

			QString sqlCmd = QString("insert into %1 values(\"%2\",\"%3\")").arg(shName).arg(tempC1).arg(tempC2);
			query.exec(sqlCmd);
			error = query.lastError().databaseText();
			//需判断错误情况，并给出相应提示信息	
		}
	}
	if (error.isEmpty())
	{
		/*QMessageBox msgBox;
		msgBox.setWindowTitle("提示");
		msgBox.setText("数据导入成功！");
		msgBox.exec();*/
		QMessageBox::information(this, QStringLiteral("提示"), "数据导入成功！", QMessageBox::Yes);
	}

}

//点击treeView的某个项目，获取该参数的英文参数名，即数据库表名
void FlyEdit::paraSelectAndShow()
{
	
	QItemSelectionModel *selectionModel = ui.treeView_paraList->selectionModel();
	QModelIndex index = selectionModel->currentIndex();
	//QString text = QString("(%1,%2)").arg(index.row()).arg(index.column());//text=(rownumber,colnumber),index.row()=rownumber
	index = index.sibling(index.row(), 1);
	QMap<int, QVariant> rowMap = m_paraListmodel->itemData(index);
	//QVariant value = rowMap.value(1, QVariant());
	QString paraName;
	if(rowMap.contains(2))
	{
		QVariant value = rowMap.value(2);
		paraName = value.toString();
	}
	//return m_paraName;
	if (paraName.isEmpty())
	{
		QMessageBox::warning(NULL, QStringLiteral("提示"), "请在左侧选择参数！", QMessageBox::Yes);
		return;
	}
	m_model->clear();
	m_model->setTable(paraName);
	m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_model->setSort(0, Qt::AscendingOrder);//升序排序
	m_model->select();
	//m_model->lastError();//怎么看错误代码？
	//m_model->setHeaderData(0, Qt::Horizontal, tr("Name"));
	//m_model->setHeaderData(1, Qt::Horizontal, tr("Salary"));
	ui.tableView_Para1->setModel(m_model);
	ui.tableView_Para1->resizeColumnToContents(0);//根据内容自适应列宽
	ui.tableView_Para1->show();
}

//提交修改
void FlyEdit::onSubmit()
{
	m_model->database().transaction();//开始事务操作

	if (m_model->submitAll()) // 提交所有被修改的数据到数据库中
	{
		if (m_model->database().commit())//提交//提交成功，事务将真正修改数据库数据
			QMessageBox::information(this, "提示", tr("数据修改成功!"));
	}
	else
	{
		m_model->database().rollback();//提交失败，事务回滚
		QMessageBox::warning(this, "提示", tr("数据库错误： %1").arg(m_model->lastError().text()), QMessageBox::Ok);
	}

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

void FlyEdit::onExportToExcel()
{
	QString saveExcelFileName = QFileDialog::getSaveFileName(this, "保存为", m_path, "Excel 工作簿(*.xlsx);;Excel 97-2003 工作簿(*.xls)");
	if (saveExcelFileName == "")
	{
		return;
	}
	QFile::remove(saveExcelFileName);
	QXlsx::Document xlsx(saveExcelFileName);
	//xlsx.save();//调试用
	QString error;
	QSqlQuery query(m_db);
	QString sqlCmdSelect = QString("SELECT name FROM sqlite_master WHERE type='table' ORDER BY name");
	query.exec(sqlCmdSelect);
	//error = query.lastError().databaseText();
	QStringList tableNames;
	while (query.next()) 
	{
		tableNames.append(query.value(0).toString());
		xlsx.addSheet(query.value(0).toString());
	}
	xlsx.deleteSheet("sheet1");//因为新创建的Excel文件默认有一个名字为”sheet1“的sheet
	for (int i = 0; i < tableNames.size(); ++i) 
	{
		QString sqlCmdTableColName = QString("PRAGMA table_info([%1])").arg(tableNames.at(i));
		query.exec(sqlCmdTableColName);
		xlsx.selectSheet(tableNames.value(i));
		int nColCount = 0;//字段数，即该表有几列
		while (query.next()) 
		{
			//qDebug() << query.value(1).toString();
			xlsx.write(1, nColCount+1, query.value(1).toString());
			nColCount++;
		}
		//qDebug() << nColCount;
		QSqlQuery query2(m_db);
		QString sqlCmdSelectSheet = QString("SELECT * FROM %1").arg(tableNames.at(i));
		//至此
		query2.exec(sqlCmdSelectSheet);
		int nRowCount = 0;
		while (query2.next())
		{
			for (int j = 0; j < nColCount; ++j)
			{
				//qDebug() << query2.value(j).toString();
				xlsx.write(nRowCount + 2, j + 1, query2.value(j).toString());
			}
			nRowCount++;
		}
		
	}
	
	xlsx.save();
}