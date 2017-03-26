#ifndef STOCK_H
#define STOCK_H
#include <QString>

class Stock
{
public:
	Stock(QString code, double priceLessThan, double priceMoreThan);
	QString code;
	QString prefix;
	double priceLessThan;
	double priceMoreThan;
};

#endif
