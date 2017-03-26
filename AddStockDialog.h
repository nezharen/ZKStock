#ifndef ADD_STOCK_DIALOG_H
#define ADD_STOCK_DIALOG_H
#include <QDialog>
#include "Stock.h"

class QLabel;
class QLineEdit;
class QHBoxLayout;
class QVBoxLayout;

class AddStockDialog : public QDialog
{
	Q_OBJECT
public:
	AddStockDialog();
signals:
	void stockReadyToAdd(Stock stock);
protected slots:
	void addStock();
private:
	QLabel *codeLabel, *priceLessThanLabel, *priceMoreThanLabel;
	QLineEdit *codeEdit, *priceLessThanEdit, *priceMoreThanEdit;
	QPushButton *addButton, *exitButton;
	QHBoxLayout *topLayout, *bottomLayout;
	QVBoxLayout *leftLayout, *rightLayout, *mainLayout;
};

#endif
