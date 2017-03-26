#include "Stock.h"

Stock::Stock(QString code, double priceLessThan, double priceMoreThan)
{
	this->code = code;
	if (code > QString("600"))
		prefix = QString("sh");
	else
		prefix = QString("sz");
	this->priceLessThan = priceLessThan;
	this->priceMoreThan = priceMoreThan;
}
