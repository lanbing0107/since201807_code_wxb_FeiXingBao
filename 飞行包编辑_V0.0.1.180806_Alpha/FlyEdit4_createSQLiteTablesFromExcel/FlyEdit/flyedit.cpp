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

//���캯����ʵ�ֳ�ʼ��������ĳ�Ա������m_xxxx���ڴ˺�����ʵ����
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
	m_path = QDir::currentPath();//������QDir::setCurrent(const QString &path)���ù���Ŀ¼
	QString dataBasePathName = m_path.append("/test_flyEdit.db");
	m_db.setDatabaseName(dataBasePathName);//�������ݿ���
	bool ok = m_db.open();
	
	setupTreeView();
}

FlyEdit::~FlyEdit()
{
	m_db.close();
}

//���а������б����ĳ�ʼ����������һ�ε����Excel����������ݿ�ı���Ϣ
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
	m_paraListmodel->setTable("paralist");//�ܱ�������paralist������Ƕ����ģ�����������
	m_paraListmodel->select();
	ui.treeView_paraList->setModel(m_paraListmodel);
	ui.treeView_paraList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.treeView_paraList->hideColumn(1);
	ui.treeView_paraList->resizeColumnToContents(0);//������������Ӧ�п�
	ui.treeView_paraList->show();
}

//��Excel�������в������ݣ����������ܱ�sheet��ÿ��������sheet��
void FlyEdit::onImportExcel()
{
	QString excelFileName = QFileDialog::getOpenFileName(this, tr("ѡ��Excel�ļ�"), m_path, tr("Excel ������(*.xlsx);;Excel 97-2003 ������(*.xls)"));
	if (excelFileName == "")
	{
		return;
	}
	//-------------------------------------------------------//
	//if�ж��ļ���ʽ�����ݣ�����һ��int���ͱ����������¼�Ƿ���ȷ���ҷ��ϸ�ʽ���ݣ�������ʾ����treeView�в���ʾ

	//------------------------ɾ�����ݿ�ԭ�б�-----------------------------//
	QSqlQuery query(m_db);
	QString sqlCmdSelectOldTable = QString("SELECT name FROM sqlite_master WHERE type='table' ORDER BY name");
	query.exec(sqlCmdSelectOldTable);
	QString error;
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
		error = query2.lastError().databaseText();
	}
	
	//---------------------��Excel��sheet���������ݿ��--------------------//
	QXlsx::Document xlsx(excelFileName);
	QStringList sheetNames = xlsx.sheetNames();//Excel�ļ���sheet������sheet��������0��ʼ
	int sheetNumber = sheetNames.size();//sheet��������0��ʼ
	for (int i = 0; i < sheetNumber; ++i)
	{
		QString shName = sheetNames.value(i);//QString shName2 = sheetnames.at(i);
		xlsx.selectSheet(shName);
		QXlsx::CellRange range = xlsx.dimension();
		int rowCounts = range.lastRow();//��ȡ���ļ������һ�У�ע�⣬������һ���пո�ҲΪ��Ч�У�
		int colCounts = range.lastColumn();//��ȡ���ļ������һ��
		QString sqlCmdCreateTable;
		QString fieldNameAndTypes;
		//���ֶ���������ƴ���ַ������������洴����Ӧ�����ݿ��
		for (int j = 1; j < colCounts + 1; ++j)//���м������ֶ�
		{
			QString fieldName = xlsx.read(1, j).toString();//�õ�Ҫ�������ݿ�����ֶ���
			fieldName.append(" TEXT NOT NULL,");//���ֶ�����ȫ������ΪTEXT�����Ҳ���Ϊ�գ���NOT NULL
			fieldNameAndTypes.append(fieldName);
		}
		int lastIndexOfComma = fieldNameAndTypes.lastIndexOf(",");//�ַ�λ����0��ʼ����
		fieldNameAndTypes.remove(lastIndexOfComma, 1);//�õ���Ҫ�������ݿ�����ֶ���������
		sqlCmdCreateTable = QString("CREATE TABLE %1(%2)").arg(shName).arg(fieldNameAndTypes);
		query2.exec(sqlCmdCreateTable);
		//QString error = query2.lastError().databaseText();
		//-----------��Excel����д�����ݿ�----------//
		//һ��һ�еض���д
		for (int ir = 2; ir < rowCounts + 1; ++ir)
		{
			QString rowFieldValues = "\"";
			QString sqlCmdInsertRowFieldValues;
			//��ÿ�еĸ���ƴΪһ��QStringList�����������ݿ����д
			for (int ic = 1; ic < colCounts + 1; ++ic)
			{
				QString fieldValue = xlsx.read(ir, ic).toString();
				fieldValue.append("\",\"");
				rowFieldValues.append(fieldValue);
			}
			lastIndexOfComma = rowFieldValues.lastIndexOf(",\"");
			rowFieldValues.remove(lastIndexOfComma, 2);
			sqlCmdInsertRowFieldValues = QString("INSERT INTO %1 VALUES(%2)").arg(shName).arg(rowFieldValues);
			query2.exec(sqlCmdInsertRowFieldValues);
			error = query2.lastError().databaseText();
		}
	}

	
	if (error.isEmpty())
	{
		/*QMessageBox msgBox;
		msgBox.setWindowTitle("��ʾ");
		msgBox.setText("���ݵ���ɹ���");
		msgBox.exec();*/
		QMessageBox::information(this, QStringLiteral("��ʾ"), "���ݵ���ɹ���", QMessageBox::Yes);
	}

}

//���treeView��ĳ����Ŀ����ȡ�ò�����Ӣ�Ĳ������������ݿ����
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
		QMessageBox::warning(NULL, QStringLiteral("��ʾ"), "�������ѡ�������", QMessageBox::Yes);
		return;
	}
	m_model->clear();
	m_model->setTable(paraName);
	m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_model->setSort(0, Qt::AscendingOrder);//��������
	m_model->select();
	//m_model->lastError();//��ô��������룿
	//m_model->setHeaderData(0, Qt::Horizontal, tr("Name"));
	//m_model->setHeaderData(1, Qt::Horizontal, tr("Salary"));
	ui.tableView_Para1->setModel(m_model);
	ui.tableView_Para1->resizeColumnToContents(0);//������������Ӧ�п�
	//ui.tableView_Para1->resizeColumnToContents(1);
	ui.tableView_Para1->show();
}

//�ύ�޸�
void FlyEdit::onSubmit()
{
	m_model->database().transaction();//��ʼ�������

	if (m_model->submitAll()) // �ύ���б��޸ĵ����ݵ����ݿ���
	{
		if (m_model->database().commit())//�ύ//�ύ�ɹ������������޸����ݿ�����
			QMessageBox::information(this, "��ʾ", tr("�����޸ĳɹ�!"));
	}
	else
	{
		m_model->database().rollback();//�ύʧ�ܣ�����ع�
		QMessageBox::warning(this, "��ʾ", tr("���ݿ���� %1").arg(m_model->lastError().text()), QMessageBox::Ok);
	}

}

//����δ�ύ���޸�,������δ�ύ��
void FlyEdit::onReMod()
{
	m_model->revertAll();//�����޸�
}

//����һ��
void FlyEdit::onInsRow()
{
	int curRow = ui.tableView_Para1->currentIndex().row();
	if (ui.radioButton_Down->isChecked())
	{
		m_model->insertRow(curRow + 1);//�ڵ�ǰ���²���һ��
	}
	else
	{
		m_model->insertRow(curRow);//�ڵ�ǰ���ϲ���һ��
	}
}

//ɾ��ѡ����
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
		if (rowMapIterator.hasPrevious())//��while?
		{
			rowMapIterator.previous();
			rowToDel = rowMapIterator.key();
			m_model->removeRow(rowToDel);
		}
	}
	int ok = QMessageBox::warning(this, "ɾ���У�", "��ȷ��ɾ����ѡ����", QMessageBox::Yes, QMessageBox::No);
	if (ok == QMessageBox::No)
	{
		m_model->revertAll();//�ύ�������ݿ���ɾ������
	}
	else
	{
		m_model->submitAll();//�����ɾ��������
	}

}

void FlyEdit::onExportToExcel()
{
	QString saveExcelFileName = QFileDialog::getSaveFileName(this, "����Ϊ", m_path, "Excel ������(*.xlsx);;Excel 97-2003 ������(*.xls)");
	if (saveExcelFileName == "")
	{
		return;
	}
	QFile::remove(saveExcelFileName);
	QXlsx::Document xlsx(saveExcelFileName);
	//xlsx.save();//������
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
	xlsx.deleteSheet("sheet1");//��Ϊ�´�����Excel�ļ�Ĭ����һ������Ϊ��sheet1����sheet
	for (int i = 0; i < tableNames.size(); ++i) 
	{
		QString sqlCmdTableColName = QString("PRAGMA table_info([%1])").arg(tableNames.at(i));
		query.exec(sqlCmdTableColName);
		xlsx.selectSheet(tableNames.value(i));
		int nColCount = 0;//�ֶ��������ñ��м���
		while (query.next()) 
		{
			//qDebug() << query.value(1).toString();
			xlsx.write(1, nColCount+1, query.value(1).toString());
			nColCount++;
		}
		//qDebug() << nColCount;
		QSqlQuery query2(m_db);
		QString sqlCmdSelectSheet = QString("SELECT * FROM %1").arg(tableNames.at(i));
		//����
		query2.exec(sqlCmdSelectSheet);
		error = query2.lastError().databaseText();
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
	if (error.isEmpty())
	{
		QMessageBox::information(this, QStringLiteral("��ʾ"), "���ݵ����ɹ���", QMessageBox::Yes);
	}
	
}