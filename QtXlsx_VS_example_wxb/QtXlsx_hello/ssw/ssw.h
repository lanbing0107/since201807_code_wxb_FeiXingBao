#ifndef SSW_H
#define SSW_H

#include <QtWidgets/QMainWindow>
#include "ui_ssw.h"

class ssw : public QMainWindow
{
	Q_OBJECT

public:
	ssw(QWidget *parent = 0);
	~ssw();

private:
	Ui::sswClass ui;
};

#endif // SSW_H
