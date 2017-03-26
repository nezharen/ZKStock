#include <QtGui>
#include "AddStockDialog.h"
#include "MainWindow.h"

MainWindow::MainWindow()
{
	createSystemTrayIcon();
	createAction();
	createMenu();
	loadData();

	addStockDialog = NULL;
	statusBar();
	setWindowTitle(tr("ZKStock"));
	setWindowIcon(QIcon(":/images/ZKStock.png"));
	show();
}

void MainWindow::createAction()
{
	addAction = new QAction(tr("&Add"), this);
	addAction->setStatusTip(tr("Add stock."));
	connect(addAction, SIGNAL(triggered()), this, SLOT(showAddStockDialog()));
	exitAction = new QAction(tr("&Exit"), this);
	exitAction->setStatusTip(tr("Exit ZKStock."));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(getClosed()));
}

void MainWindow::createMenu()
{
	stockMenu = menuBar()->addMenu(tr("&Stock"));
	stockMenu->addAction(addAction);
	stockMenu->addAction(exitAction);
}

void MainWindow::createSystemTrayIcon()
{
	systemTrayIcon = new QSystemTrayIcon(QIcon(":/images/ZKStock.png"), this);
	connect(systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(systemTrayIconActivated(QSystemTrayIcon::ActivationReason)));
	systemTrayIcon->show();
}

void MainWindow::loadData()
{
	stocks = new QList<Stock>;
}

void MainWindow::getClosed()
{
	systemTrayIcon->hide();
	close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (systemTrayIcon->isVisible())
	{
		hide();
		event->ignore();
	}
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

void MainWindow::showAddStockDialog()
{
	if (addStockDialog == NULL)
	{
		addStockDialog = new AddStockDialog;
		connect(addStockDialog, SIGNAL(stockReadyToAdd(Stock)), this, SLOT(addStock(Stock)));
	}
	addStockDialog->show();
	addStockDialog->raise();
	addStockDialog->activateWindow();
}

void MainWindow::addStock(Stock newStock)
{
	foreach (Stock stock, *stocks)
		if (stock.code == newStock.code)
		{
			QMessageBox::warning(this, tr("AddStock"), tr("This stock is already added."));
			return;
		}
	stocks->append(newStock);
}
