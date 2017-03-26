#ifndef STOCK_H
#define STOCK_H
#include <QString>

class Stock
{
public:
	Stock(QString code);
	QString code;
	QString prefix;
};

#endif
