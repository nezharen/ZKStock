#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "Stock.h"

class QAction;
class QMenu;
class AddStockDialog;
class QTableWidget;
class QHttp;
class QBuffer;
class QTextCodec;
class QTimer;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow();
protected:
	void createAction();
	void createMenu();
	void createSystemTrayIcon();
	void loadData();
	void createTable();
	void closeEvent(QCloseEvent *event);
protected slots:
	void systemTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
	void getClosed();
	void showAddStockDialog();
	void addStock(Stock newStock);
	void readHttpBuffer(bool error);
	void updateTable();
private:
	QSystemTrayIcon *systemTrayIcon;
	QAction *addAction;
	QAction *exitAction;
	QMenu *stockMenu;
	QList<Stock> *stocks;
	QTableWidget *stocksTable;
	AddStockDialog *addStockDialog;
	QHttp *http;
	QBuffer *httpBuffer;
	QTextCodec *codec;
	QTimer *timer;
	bool forceUpdate;
};

#endif
