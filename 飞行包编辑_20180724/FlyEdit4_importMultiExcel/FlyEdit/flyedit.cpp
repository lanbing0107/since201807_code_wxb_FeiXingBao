#include "flyedit.h"

#include<qsqldatabase.h>
#include<qmessagebox.h>
#include<qsqlerror.h>
#include<qsqltablemodel.h>
#include<qitemselectionmodel.h>
#include<qfiledialog.h>
#include<QtXlsx\xlsxdocument.h>
#include<qsqlquery.h>
//#include<QDebug>//VS���޷��ô˹��ܣ�Qt�п�����


//���캯������ĳ�Ա������m_xxxx���ڴ˺�����ʵ����
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
	connect(ui.pushButton_ImportExcel, SIGNAL(clicked()), this, SLOT(onImportExcel()));
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

//���а������б����ĳ�ʼ��
void FlyEdit::setupTreeView()
{
	m_paraListmodel->clear();
	m_paraListmodel->setTable("paralist");
	m_paraListmodel->select();
	ui.treeView_paraList->setModel(m_paraListmodel);
	ui.treeView_paraList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.treeView_paraList->hideColumn(1);
	ui.treeView_paraList->resizeColumnToContents(0);//������������Ӧ�п�
	ui.treeView_paraList->show();
}

//���treeView��ĳ����Ŀ����ȡ�ò�����Ӣ�Ĳ������������ݿ����
QString FlyEdit::paraSelect()
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

void FlyEdit::onImportExcel()
{
	QString path = QDir::currentPath();//������QDir::setCurrent(const QString &path)���ù���Ŀ¼
	QString excelFileName = QFileDialog::getOpenFileName(this, tr("ѡ��Excel�ļ�"), path, tr("Excel Files(*.xls *.xlsx)"));
	//-------------------------------------------------------//
	//if�ж��ļ���ʽ�����ݣ�����һ��int���ͱ����������¼�Ƿ���ȷ���ҷ��ϸ�ʽ���ݣ�������ʾ����treeView�в���ʾ
	QXlsx::Document xlsx(excelFileName);
	QStringList sheetNames = xlsx.sheetNames();//Excel�ļ���sheet����
	int sheetNumber = sheetNames.size();//sheet��������0��ʼ
	//QString shName = sheetNames.value(2);//QString shName2 = sheetnames.at(2);
	for (int i = 0; i < sheetNumber; ++i)
	{
		QString shName = sheetNames.value(i);
		xlsx.selectSheet(shName);
		QXlsx::CellRange range = xlsx.dimension();
		int rowCounts = range.lastRow();//��ȡ���ļ������һ�У�ע�⣬������һ���пո�ҲΪ��Ч�У�
		int colCounts = range.lastColumn();//��ȡ���ļ������һ��
		QSqlQuery query(m_db);
		QString error;
		
		for (int ir = 2; ir < rowCounts + 1; ir++)
		{
			if (ir == 2)//ExcelҪ�������ݿ����ݣ�������ɾ������ԭ������
			{
				QString sqlCmdDelete = QString("delete from %1").arg(shName);
				query.exec(sqlCmdDelete);
				error = query.lastError().databaseText();
				//���жϴ����������������Ӧ��ʾ��Ϣ	
			}
			QString tempC1 = xlsx.read(ir, 1).toString();
			double tempC2 = xlsx.read(ir, 2).toDouble();

			QString sqlCmd = QString("insert into %1 values(\"%2\",%3)").arg(shName).arg(tempC1).arg(tempC2);
			query.exec(sqlCmd);
			error = query.lastError().databaseText();
			//���жϴ����������������Ӧ��ʾ��Ϣ	
		}
	}

	//xlsx.selectSheet(m_paraName);
	//QXlsx::CellRange range = xlsx.dimension();
	//int rowCounts = range.lastRow();//��ȡ���ļ������һ�У�ע�⣬������һ���пո�ҲΪ��Ч�У�
	//int colCounts = range.lastColumn();//��ȡ���ļ������һ��
	////QSqlDatabase::database().transaction();
	/*QSqlQuery query(m_db);
	QString error;
	for (int ir = 2; ir < rowCounts + 1; ir++)
	{
		QString tempC1 = xlsx.read(ir, 1).toString();
		double tempC2 = xlsx.read(ir, 2).toDouble();

		QString sqlCmd = QString("insert into %1 values(\"%2\",%3)").arg(m_paraName).arg(tempC1).arg(tempC2);
		query.exec(sqlCmd);
		error = query.lastError().databaseText();
		//���жϴ����������������Ӧ��ʾ��Ϣ	
		
	}*/
	//if (error == "")
	//{
	//	QMessageBox msgBox;
	//	//QMessageBox::information(this,"��ѡ�������ݵ���ɹ���");
	//	QSqlDatabase::database().commit();
	//	msgBox.setText("�������ݵ���ɹ���");
	//}
	//else
	//{
	//	QSqlDatabase::database().rollback();
	//	QMessageBox::warning(this, QStringLiteral("��ʾ"), "�������ݵ���ʧ�ܣ�", QMessageBox::Yes);
	//}
	
}


//����Ӣ�Ĳ������������ݿ����������ĳһ��MySQL���
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
	if (m_paraName.isEmpty())
	{
		return;
	}
	m_model->clear();
	m_model->setTable(m_paraName);
	m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_model->setSort(0, Qt::AscendingOrder);//��������
	m_model->select();
	//m_model->lastError();//��ô��������룿
	//m_model->setHeaderData(0, Qt::Horizontal, tr("Name"));
	//m_model->setHeaderData(1, Qt::Horizontal, tr("Salary"));
	ui.tableView_Para1->setModel(m_model);
	ui.tableView_Para1->resizeColumnToContents(0);//������������Ӧ�п�
	ui.tableView_Para1->show();

	////db.close();
}

//�ύ�޸�
void FlyEdit::onSubmit()
{
	m_model->database().transaction();//��ʼ�������
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

	//	QMessageBox::information(this, "tableModel", tr("���ݲ���Ϊ�գ�"));
	//	onImport();
	//}
	//else
	//{
		if (m_model->submitAll()) // �ύ���б��޸ĵ����ݵ����ݿ���
		{
			if (m_model->database().commit())//�ύ//�ύ�ɹ������������޸����ݿ�����
				QMessageBox::information(this, "tableModel", tr("�����޸ĳɹ�!"));
		}
		else
		{
			m_model->database().rollback();//�ύʧ�ܣ�����ع�
			QMessageBox::warning(this, "tableModel", tr("���ݿ���� %1").arg(m_model->lastError().text()), QMessageBox::Ok);
		}
	//}

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