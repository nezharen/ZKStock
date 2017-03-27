#include <QtGui>
#include "SetStockDialog.h"

SetStockDialog::SetStockDialog(Stock stock)
{
	codeLabel = new QLabel(tr("Code:"));
	codeEdit = new QLineEdit;
	codeEdit->setText(stock.code);
	codeEdit->setAlignment(Qt::AlignHCenter);
	codeEdit->setEnabled(false);

	priceLessThanLabel = new QLabel(tr("Warn when price &less than:"));
	priceLessThanEdit = new QLineEdit;
	priceLessThanEdit->setText(QString::number(stock.priceLessThan));
	priceLessThanEdit->setAlignment(Qt::AlignHCenter);
	priceLessThanLabel->setBuddy(priceLessThanEdit);

	priceMoreThanLabel = new QLabel(tr("Warn when price &more than:"));
	priceMoreThanEdit = new QLineEdit;
	priceMoreThanEdit->setText(QString::number(stock.priceMoreThan));
	priceMoreThanEdit->setAlignment(Qt::AlignHCenter);
	priceMoreThanLabel->setBuddy(priceMoreThanEdit);

	setButton = new QPushButton(tr("&Set"));
	setButton->setDefault(true);
	exitButton = new QPushButton(tr("&Exit"));

	connect(setButton, SIGNAL(clicked()), this, SLOT(setStock()));
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
	bottomLayout->addWidget(setButton);
	bottomLayout->addStretch();
	bottomLayout->addWidget(exitButton);

	mainLayout = new QVBoxLayout;
	mainLayout->addLayout(topLayout);
	mainLayout->addLayout(bottomLayout);

	setLayout(mainLayout);
	setWindowTitle(tr("Set Stock"));
}

void SetStockDialog::setStock()
{
	bool ok;
	double priceLessThan, priceMoreThan;
	priceLessThan = priceLessThanEdit->text().toDouble(&ok);
	if (!ok)
		priceLessThan = 0.0;
	priceMoreThan = priceMoreThanEdit->text().toDouble(&ok);
	if (!ok)
		priceMoreThan = 100.0;
	Stock stock(codeEdit->text(), priceLessThan, priceMoreThan);
	emit stockReadyToSet(stock);
	close();
}
