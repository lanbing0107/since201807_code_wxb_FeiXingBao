#include "ssw.h"
#include <QtWidgets/QApplication>

#include <QtXlsx\xlsxdocument.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ssw w;
	w.show();

	////------------------------hello--------------------------------////
	//![0]
	QXlsx::Document xlsx("d:/wxb/ssw/test.xlsx");
	//![0]
	//![1]
	xlsx.write("A1", "Hello Qt!");
	xlsx.write("A2", 12345);
	xlsx.write("A3", "=44+33");
	xlsx.write("A4", true);
	//![2]
	xlsx.save();
	//------------------------hello--------------------------------//

	return a.exec();
}
