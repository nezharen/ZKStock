#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "Stock.h"

class QAction;
class QMenu;
class AddStockDialog;

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
	void closeEvent(QCloseEvent *event);
protected slots:
	void systemTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
	void getClosed();
	void showAddStockDialog();
	void addStock(Stock newStock);
private:
	QSystemTrayIcon *systemTrayIcon;
	QAction *addAction;
	QAction *exitAction;
	QMenu *stockMenu;
	QList<Stock> *stocks;
	AddStockDialog *addStockDialog;
};

#endif
