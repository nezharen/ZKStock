#include "Stock.h"

Stock::Stock(QString code)
{
	this->code = code;
	if (code > QString("600"))
		prefix = QString("sh");
	else
		prefix = QString("sz");
}
