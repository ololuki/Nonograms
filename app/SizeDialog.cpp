#include "SizeDialog.h"
#include "ui_sizedialog.h"

#include <QSpinBox>


SizeDialog::SizeDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SizeDialog)
{
	ui->setupUi(this);
}

SizeDialog::~SizeDialog()
{
	delete ui;
}

size_t SizeDialog::getWidth()
{
	return static_cast<size_t>(ui->widthSpinBox->value());
}

size_t SizeDialog::getHeight()
{
	return static_cast<size_t>(ui->heightSpinBox->value());
}
