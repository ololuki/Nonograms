#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SizeDialog.h"
#include <QDebug>

#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	recreateField(14, 10);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionNew_triggered()
{
	if (!abandonChangesOrSavePrompt()) return;
	
	SizeDialog *d = new SizeDialog(this);
	qDebug() << d->exec();
	size_t width = d->getWidth();
	size_t height = d->getHeight();
	delete d;
	
	recreateField(width, height);
}

bool MainWindow::abandonChangesOrSavePrompt()
{
	auto answer = QMessageBox::question(this,
								"Unsaved changes",
								"Do you want to save changes?",
								QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel));
	if (answer == QMessageBox::Yes) {
		//on_actionSave_triggered();
		//if (isDirty()) 
			return false;
	} else if (answer == QMessageBox::Cancel) {
		return false;
	}

    return true;
}

void MainWindow::on_actionAdd_blocks_triggered()
{
	if (field->getWidth() < 3 || field->getHeight() < 8) return;
	field->setPixel(Pixel(AddressOnDrawingArea(2,5), pixelSign::SGN_FILL_BLACK));
	field->setPixel(Pixel(AddressOnDrawingArea(2,7), pixelSign::SGN_FILL_BLACK));
	field->updateBlockDescription(BlockDescription(AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, 2, 0), 1));
	field->addDescriptionAtEnd(BlockDescription(AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, 2, 1), 1));
	field->updateBlockDescription(BlockDescription(AddressOnBlocksDescription(AddressOnBlocksDescription::HORIZONTAL, 5, 0), 1));
	field->updateBlockDescription(BlockDescription(AddressOnBlocksDescription(AddressOnBlocksDescription::HORIZONTAL, 7, 0), 1));
}

void MainWindow::recreateField(size_t width, size_t height)
{
	field.reset(new WholeFieldImpl(width, height));
	ui->drawingArea->setField(field);
	ui->columnsDescription->setField(field);
	ui->rowsDescription->setField(field);
}
