#ifndef SET_STOCK_DIALOG_H
#define SET_STOCK_DIALOG_H
#include <QDialog>
#include "Stock.h"

class QLabel;
class QLineEdit;
class QHBoxLayout;
class QVBoxLayout;

class SetStockDialog : public QDialog
{
	Q_OBJECT
public:
	SetStockDialog(Stock stock);
signals:
	void stockReadyToSet(Stock stock);
protected slots:
	void setStock();
private:
	QLabel *codeLabel, *priceLessThanLabel, *priceMoreThanLabel;
	QLineEdit *codeEdit, *priceLessThanEdit, *priceMoreThanEdit;
	QPushButton *setButton, *exitButton;
	QHBoxLayout *topLayout, *bottomLayout;
	QVBoxLayout *leftLayout, *rightLayout, *mainLayout;
};

#endif
