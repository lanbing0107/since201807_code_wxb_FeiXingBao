#include "qtxlsx_extractdata.h"
#include <QtWidgets/QApplication>
#include<QtXlsx\xlsxdocument.h>
#include<qdebug.h>
#include<qdatetime.h>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtXlsx_extractdata w;
	w.show();

	{//Create a new .xlsx file.
	QXlsx::Document xlsx;
    xlsx.write("A1", "Hello Qt!");
    xlsx.write("A2", 12345);
    xlsx.write("A3", "=44+33");
    xlsx.write("A4", true);
    xlsx.write("A5", "http://qt-project.org");
    xlsx.write("A6", QDate(2013, 12, 27));
    xlsx.write("A7", QTime(6, 30));
    xlsx.saveAs("Book1.xlsx");
    }

    //![0]
    QXlsx::Document xlsx("Book1.xlsx");
    //![0]
	
    //![1]
    xlsx.read("A1");
	xlsx.read("A2");
	xlsx.read("A3");
	xlsx.read("A4");
	xlsx.read("A5");
	xlsx.read("A6");
	xlsx.read("A7");
    //![1]

    //![2]
    for (int row=1; row<10; ++row) {
        if (QXlsx::Cell *cell=xlsx.cellAt(row, 1))
            qDebug()<<cell->value();
    }

	return a.exec();
}
