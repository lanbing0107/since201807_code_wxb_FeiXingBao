#ifndef QTXLSX_WORKSHEETOPERATIONS_H
#define QTXLSX_WORKSHEETOPERATIONS_H

#include <QtWidgets/QMainWindow>
#include "ui_qtxlsx_worksheetoperations.h"

class QtXlsx_worksheetoperations : public QMainWindow
{
	Q_OBJECT

public:
	QtXlsx_worksheetoperations(QWidget *parent = 0);
	~QtXlsx_worksheetoperations();

private:
	Ui::QtXlsx_worksheetoperationsClass ui;
};

#endif // QTXLSX_WORKSHEETOPERATIONS_H
