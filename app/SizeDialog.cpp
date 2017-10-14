#include "SizeDialog.h"
#include "ui_sizedialog.h"

#include <QSpinBox>


SizeDialog::SizeDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SizeDialog)
{
	ui->setupUi(this);
	this->setWindowTitle("Enter new field sizes");
}

SizeDialog::~SizeDialog()
{
	delete ui;
}

int SizeDialog::getWidth()
{
	return ui->widthSpinBox->value();
}

int SizeDialog::getHeight()
{
	return ui->heightSpinBox->value();
}
