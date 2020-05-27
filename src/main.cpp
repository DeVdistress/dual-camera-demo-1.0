#include <qglobal.h>
#include <QApplication>
#include <QLabel>

#if QT_VERSION < 0x050000
#include <QWSServer>
#endif


#include <QPushButton>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	// у меня не получилось запустить скрипт под дебагом с начальным ./dual_camera -platform linuxfb 1
	// замутил этот скрипт
	int argc_my = 4;
	char *argv_my[argc_my] = {(char*)"./dual_camera", (char*)"-platform", (char*)"linuxfb", (char*)"1"};
	argc = argc_my;
	argv[0] = argv_my[0];
	argv[1] = argv_my[1];
	argv[2] = argv_my[2];
	argv[3] = argv_my[3];

	bool use_cmem = false;

	if(argc > 3)
	{
		use_cmem = atoi(argv[3]);
	}
	else
	{
		printf("USAGE: -platform linuxfb <use_cmem flag>\n\n");
		printf("Set the ""use_cmem"" flag to 1 to allocate memory from CMEM driver. By default it is set to 0\n\n\n");
	}

	QApplication a(argc, argv);

	printf("++ use_cmem %d\n\n", use_cmem);

	MainWindow w(NULL, use_cmem);

#if QT_VERSION < 0x050000
	QWSServer::setBackground(QBrush(QColor(0, 0, 0, 0)));
#endif

	w.show();
	return a.exec();
}

