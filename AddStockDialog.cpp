#include <QtGui>
#include "AddStockDialog.h"
#define CODE_LENGTH 6

AddStockDialog::AddStockDialog()
{
	codeLabel = new QLabel(tr("&Code:"));
	codeEdit = new QLineEdit;
	codeEdit->setAlignment(Qt::AlignHCenter);
	codeLabel->setBuddy(codeEdit);

	addButton = new QPushButton(tr("&Add"));
	addButton->setDefault(true);
	exitButton = new QPushButton(tr("&Exit"));

	connect(addButton, SIGNAL(clicked()), this, SLOT(addStock()));
	connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));

	leftLayout = new QVBoxLayout;
	leftLayout->addWidget(codeLabel);

	rightLayout = new QVBoxLayout;
	rightLayout->addWidget(codeEdit);

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
	Stock stock(codeEdit->text());
	emit stockReadyToAdd(stock);
	close();
}
