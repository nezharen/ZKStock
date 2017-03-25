#include <QCloseEvent>
#include "MainWindow.h"

MainWindow::MainWindow()
{
	systemTrayIcon = new QSystemTrayIcon(this);
	connect(systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(systemTrayIconActivated(QSystemTrayIcon::ActivationReason)));
	systemTrayIcon->show();
	setWindowTitle(tr("ZKStock"));
	show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (systemTrayIcon->isVisible())
	{
		hide();
		event->ignore();
	}
	else
		event->accept();
}

void MainWindow::systemTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
	case QSystemTrayIcon::Trigger:
		if (isVisible())
			hide();
		else
			show();
		break;
	default:
		break;
	}
}
