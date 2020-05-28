#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QMutex>
#include "loopback.h"
#include <stdio.h>

class MyThread : public QThread
{
	Q_OBJECT

protected:
	void run();
};

MyThread* loopback;
QMutex drm_resource;

MainWindow::MainWindow(QWidget *parent, bool use_cmem) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->setAttribute(Qt::WA_TranslucentBackground);
	this->setWindowFlags(Qt::FramelessWindowHint);

	status.use_cmem = use_cmem;

	loopback = new MyThread();

	if(init_loopback() < 0) {
		/* TODO: make sure exit occurs properly */
	}

	/* Configure GUI */
	this->setFixedSize(status.display_xres, status.display_yres);
	ui->frame->setGeometry(0, 0, status.display_xres, status.display_yres);

	/* Set the back ground color to black */
	/* This is a workaround required when moving from Qt4 to QT5.  */
	/* QT5 doesn't support QWSServer. This is causing the graphics */
	/* windows not to clear up when being instructed to be hidden  */
	/* Making the background color black solves the problem        */
	ui->frame->setStyleSheet("background-color:black;");
	ui->frame->show();

#ifndef PIP_POS_X
	#define PIP_POS_X  25
#endif
#ifndef PIP_POS_Y
	#define PIP_POS_Y  25
#endif

	ui->frame_pip->setGeometry(PIP_POS_X, PIP_POS_Y, status.display_xres/3, status.display_yres/3);
	ui->frame_pip_2->setGeometry(status.display_xres - status.display_xres/3 - PIP_POS_X, PIP_POS_Y, status.display_xres/3, status.display_yres/3);

	ui->frame_pip_3->setGeometry(PIP_POS_X, status.display_yres/3 + PIP_POS_Y - 2, status.display_xres/3, status.display_yres/3);
	ui->frame_pip_4->setGeometry(status.display_xres - status.display_xres/3 - PIP_POS_X, status.display_yres/3 + PIP_POS_Y - 2, status.display_xres/3, status.display_yres/3);

#if(1)
	ui->capture->setGeometry(status.display_xres/2 - 330,
		status.display_yres - 50,
		71, 21);

	ui->switch_2->setGeometry(status.display_xres/2 - 230,
		status.display_yres - 50,
		71, 21);

	ui->pip->setGeometry(status.display_xres/2 - 130,
		status.display_yres - 50,
		71, 21);

	ui->pip_2->setGeometry(status.display_xres/2 - 30,
		status.display_yres - 50,
		71, 21);

	ui->pip_3->setGeometry(status.display_xres/2 + 70,
		status.display_yres - 50,
		71, 21);

	ui->pip_4->setGeometry(status.display_xres/2 + 170,
		status.display_yres - 50,
		71, 21);

	ui->exit->setGeometry(status.display_xres/2 + 270,
		status.display_yres - 50,
		71, 21);
#endif

	if(status.num_cams == 1)
	{
		// Reconfigure GUI to reflect single camera mode
		ui->pip->setHidden(true);
		ui->pip->setDisabled(true);
		ui->pip_2->setHidden(true);
		ui->pip_2->setDisabled(true);
		ui->pip_3->setHidden(true);
		ui->pip_3->setDisabled(true);
		ui->pip_4->setHidden(true);
		ui->pip_4->setDisabled(true);
		ui->switch_2->setHidden(true);
		ui->switch_2->setDisabled(true);
		ui->frame_pip->setHidden(true);

		// DeVdistress Don't resize
#if(0)
		ui->capture->setGeometry(status.display_xres/2 - 100,
			status.display_yres - 50,
			71, 21);
		ui->exit->setGeometry(status.display_xres/2 + 10,
			status.display_yres - 50,
			71, 21);
#endif
	}
	ui->frame_pip_3->setHidden(true);
	ui->frame_pip_4->setHidden(true);
	ui->pip_2->setHidden(true);
	ui->pip_2->setDisabled(true);
	ui->pip_3->setHidden(true);
	ui->pip_3->setDisabled(true);
	ui->pip_4->setHidden(true);
	ui->pip_4->setDisabled(true);

	// Start the camera loopback thread
	loopback->start();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_capture_clicked()
{
	status.jpeg=true;
}

void MainWindow::on_switch_2_clicked()
{
	/* While changing the drm display properties, make sure loopback thread */
	/* isn't running thereby accessing drm properties  simultaneously, and  */ 
	/* hence can cause system crash                                         */
	drm_resource.lock();

	if (status.num_cams > 1)
	{
		//switch the main camera by toggleing the main_cam value.
		status.main_cam = !status.main_cam;
		set_plane_properties();
	}

	drm_resource.unlock();
}

void MainWindow::on_pip_clicked()
{
	/* While changing the drm display properties, make sure loopback thread */
	/* isn't running thereby accessing drm properties  simultaneously, and  */ 
	/* hence can cause system crash                                         */
	drm_resource.lock();

	if (status.pip==true)
	{
		status.pip=false;
		drm_disable_pip();
		ui->frame_pip->setHidden(true);
		ui->frame_pip_2->setHidden(true);
	}
	else
	{
		drm_enable_pip();
		ui->frame_pip->setHidden(false);
		ui->frame_pip_2->setHidden(false);
		status.pip=true;
	}

	drm_resource.unlock();
}

void MainWindow::on_pip_2_clicked()
{
	/* While changing the drm display properties, make sure loopback thread */
	/* isn't running thereby accessing drm properties  simultaneously, and  */
	/* hence can cause system crash                                         */
	drm_resource.lock();

	if (status.pip==true)
	{
		status.pip=false;
//		drm_disable_pip_2();
		ui->frame_pip_2->setHidden(true);
	}
	else
	{
//		drm_enable_pip_2();
		ui->frame_pip_2->setHidden(false);
		status.pip=true;
	}

	drm_resource.unlock();
}

void MainWindow::on_pip_3_clicked()
{
	/* While changing the drm display properties, make sure loopback thread */
	/* isn't running thereby accessing drm properties  simultaneously, and  */
	/* hence can cause system crash                                         */
	drm_resource.lock();

	if (status.pip==true)
	{
		status.pip=false;
//		drm_disable_pip_3();
		ui->frame_pip_3->setHidden(true);
	}
	else
	{
//		drm_enable_pip_3();
		ui->frame_pip_3->setHidden(false);
		status.pip=true;
	}

	drm_resource.unlock();
}

void MainWindow::on_pip_4_clicked()
{
	/* While changing the drm display properties, make sure loopback thread */
	/* isn't running thereby accessing drm properties  simultaneously, and  */
	/* hence can cause system crash                                         */
	drm_resource.lock();

	if (status.pip==true)
	{
		status.pip=false;
//		drm_disable_pip_4();
		ui->frame_pip_4->setHidden(true);
	}
	else
	{
//		drm_enable_pip_4();
		ui->frame_pip_4->setHidden(false);
		status.pip=true;
	}

	drm_resource.unlock();
}

void MainWindow::on_exit_clicked()
{
	status.exit=true;
	loopback->wait(1000);
	this->close();
}

void MyThread::run()
{

	while(status.exit == false)
	{
		drm_resource.lock();
		process_frame();
		drm_resource.unlock();	
		msleep(1);
	}
	end_streaming();
	exit_devices();
}


#include "mainwindow.moc"
