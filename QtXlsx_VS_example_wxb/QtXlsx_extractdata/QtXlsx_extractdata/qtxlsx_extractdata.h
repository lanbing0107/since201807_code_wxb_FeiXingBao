#ifndef QTXLSX_EXTRACTDATA_H
#define QTXLSX_EXTRACTDATA_H

#include <QtWidgets/QMainWindow>
#include "ui_qtxlsx_extractdata.h"

class QtXlsx_extractdata : public QMainWindow
{
	Q_OBJECT

public:
	QtXlsx_extractdata(QWidget *parent = 0);
	~QtXlsx_extractdata();

private:
	Ui::QtXlsx_extractdataClass ui;
};

#endif // QTXLSX_EXTRACTDATA_H
