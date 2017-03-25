#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow();
protected:
	void closeEvent(QCloseEvent *event);
private slots:
	void systemTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
private:
	QSystemTrayIcon *systemTrayIcon;
};

#endif
