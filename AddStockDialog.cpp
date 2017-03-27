#include <QtGui>
#include "AddStockDialog.h"
#define CODE_LENGTH 6

AddStockDialog::AddStockDialog()
{
	codeLabel = new QLabel(tr("&Code:"));
	codeEdit = new QLineEdit;
	codeEdit->setAlignment(Qt::AlignHCenter);
	codeLabel->setBuddy(codeEdit);

	priceLessThanLabel = new QLabel(tr("Warn when price &less than:"));
	priceLessThanEdit = new QLineEdit;
	priceLessThanEdit->setAlignment(Qt::AlignHCenter);
	priceLessThanLabel->setBuddy(priceLessThanEdit);

	priceMoreThanLabel = new QLabel(tr("Warn when price &more than:"));
	priceMoreThanEdit = new QLineEdit;
	priceMoreThanEdit->setAlignment(Qt::AlignHCenter);
	priceMoreThanLabel->setBuddy(priceMoreThanEdit);

	addButton = new QPushButton(tr("&Add"));
	addButton->setDefault(true);
	exitButton = new QPushButton(tr("&Exit"));

	connect(addButton, SIGNAL(clicked()), this, SLOT(addStock()));
	connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));

	leftLayout = new QVBoxLayout;
	leftLayout->addWidget(codeLabel);
	leftLayout->addWidget(priceLessThanLabel);
	leftLayout->addWidget(priceMoreThanLabel);

	rightLayout = new QVBoxLayout;
	rightLayout->addWidget(codeEdit);
	rightLayout->addWidget(priceLessThanEdit);
	rightLayout->addWidget(priceMoreThanEdit);

	topLayout = new QHBoxLayout;
	topLayout->addLayout(leftLayout);
	topLayout->addLayout(rightLayout);

	bottomLayout = new QHBoxLayout;
	bottomLayout->addWidget(addButton);
	bottomLayout->addStretch();
	bottomLayout->addWidget(exitButton);

	mainLayout = new QVBoxLayout;
	mainLayout->addLayout(topLayout);
	mainLayout->addLayout(bottomLayout);

	setLayout(mainLayout);
	setWindowTitle(tr("Add Stock"));
}

void AddStockDialog::addStock()
{
	if (codeEdit->text().size() != CODE_LENGTH)
	{
		QMessageBox::critical(this, tr("AddStock"), tr("Invalid code number."));
		return;
	}
	for (int i = 0; i < CODE_LENGTH; i++)
		if (codeEdit->text().at(i) < QChar('0') || codeEdit->text().at(i) > QChar('9'))
		{
			QMessageBox::critical(this, tr("AddStock"), tr("Invalid code number."));
			return;
		}
	bool ok;
	double priceLessThan, priceMoreThan;
	priceLessThan = priceLessThanEdit->text().toDouble(&ok);
	if (!ok)
		priceLessThan = 0.0;
	priceMoreThan = priceMoreThanEdit->text().toDouble(&ok);
	if (!ok)
		priceMoreThan = 100.0;
	Stock stock(codeEdit->text(), priceLessThan, priceMoreThan);
	emit stockReadyToAdd(stock);
	close();
}
