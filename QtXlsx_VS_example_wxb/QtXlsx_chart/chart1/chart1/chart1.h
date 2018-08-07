#ifndef CHART1_H
#define CHART1_H

#include <QtWidgets/QMainWindow>
#include "ui_chart1.h"

class chart1 : public QMainWindow
{
	Q_OBJECT

public:
	chart1(QWidget *parent = 0);
	~chart1();

private:
	Ui::chart1Class ui;
};

#endif // CHART1_H
