#include <QtGui>
#include <QtNetwork>
#include "AddStockDialog.h"
#include "MainWindow.h"

MainWindow::MainWindow()
{
	createSystemTrayIcon();
	createAction();
	createMenu();
	loadData();
	createTable();

	codec = QTextCodec::codecForName("GBK");
	http = new QHttp("hq.sinajs.cn", 80, this);
	connect(http, SIGNAL(done(bool)), this, SLOT(readHttpBuffer(bool)));
	addStockDialog = NULL;
	forceUpdate = false;
	timer = new QTimer(this);
	timer->setSingleShot(true);
	timer->setInterval(5000);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateTable()));

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

void MainWindow::createTable()
{
	stocksTable = new QTableWidget(this);
	stocksTable->setColumnCount(4);
	QStringList header;
	header << tr("Code") << tr("Name") << tr("Price") << tr("Rate");
	stocksTable->setHorizontalHeaderLabels(header);
	//stocksTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	stocksTable->verticalHeader()->setVisible(false);
	stocksTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	stocksTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	setCentralWidget(stocksTable);
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
	stocksTable->setRowCount(stocks->size());
	stocksTable->setItem(stocks->size() - 1, 0, new QTableWidgetItem(newStock.code));
	if (!timer->isActive())
		timer->start();
	forceUpdate = true;
}

void MainWindow::updateTable()
{
	QDate date = QDate::currentDate();
	QTime time = QTime::currentTime();
	if (!forceUpdate && (date.dayOfWeek() > 5 || !(((time.hour() > 9 || (time.hour() == 9 && time.minute() >= 30)) && (time.hour() < 11 || (time.hour() == 11 && time.minute() <= 30))) || (time.hour() >= 13 && time.hour() <= 15))))
	{
		timer->start();
		return;
	}
	if (forceUpdate)
		forceUpdate = false;
	QString path("/list=");
	for (int i = 0; i < stocks->size(); i++)
	{
		if (i > 0)
			path += QChar(',');
		path += stocks->at(i).prefix;
		path += stocks->at(i).code;
	}
	httpBuffer = new QBuffer(this);
	httpBuffer->open(QBuffer::ReadWrite);
	http->get(path, httpBuffer);
}

void MainWindow::readHttpBuffer(bool error)
{
	if (!error)
	{
		httpBuffer->seek(0);
		int ord = 0;
		while (true)
		{
			QString s = codec->toUnicode(httpBuffer->readLine());
			if (s.isEmpty())
				break;
			QStringList list = s.split("\"").at(1).split(",");
			stocksTable->setItem(ord, 0, new QTableWidgetItem(s.mid(13, 6)));

			stocksTable->setItem(ord, 1, new QTableWidgetItem(list.at(0)));
			stocksTable->setItem(ord, 2, new QTableWidgetItem(list.at(3)));
			if (stocks->at(ord).priceLessThan > list.at(3).toDouble())
			{
				systemTrayIcon->showMessage(tr("Warning"), list.at(0) + tr("'s price is less than %1").arg(stocks->at(ord).priceLessThan));
				system((tr("notify-send \"ZKStock\" \"") + list.at(0) + tr("'s price is less than %1").arg(stocks->at(ord).priceLessThan) + tr("\"")).toUtf8().data());
				(*stocks)[ord].priceLessThan = -1e9;
			}
			if (stocks->at(ord).priceMoreThan < list.at(3).toDouble())
			{
				systemTrayIcon->showMessage(tr("Warning"), list.at(0) + tr("'s price is more than %1").arg(stocks->at(ord).priceMoreThan));
				system((tr("notify-send \"ZKStock\" \"") + list.at(0) + tr("'s price is less than %1").arg(stocks->at(ord).priceLessThan) + tr("\"")).toUtf8().data());
				(*stocks)[ord].priceMoreThan = 1e9;
			}
			ord++;
		}
	}
	httpBuffer->close();
	delete httpBuffer;
	timer->start();
}
