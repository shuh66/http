#include "httptest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	httptest w;
	w.show();
	return a.exec();
}
