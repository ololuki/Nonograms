#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SizeDialog.h"
#include "file/FileWriter.h"
#include "file/FileReader.h"
#include "file/NonogramFileWriter.h"
#include "file/NonogramFileReader.h"
#include <QDebug>

#include <QMessageBox>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->setWindowTitle("Nonograms");
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
	bool isConfirmed = d->exec();
	size_t width = d->getWidth();
	size_t height = d->getHeight();
	delete d;
	if (isConfirmed)
	{
		recreateField(width, height);
	}
}

void MainWindow::on_actionOpen_triggered()
{
	if (!abandonChangesOrSavePrompt()) return;

	QString fileName =
		QFileDialog::getOpenFileName(this,
			tr("Open File"),
			QDir::currentPath(),
			tr("nonogram (*.nonogram);;All File Types (*.*)"));
	
	if (fileName.isEmpty()) return;
	
	FileReader *reader = new NonogramFileReader();
	reader->read(fileName.toStdString());
	replaceField(reader->getField());
	delete reader;
}

void MainWindow::on_actionSave_as_triggered()
{
	QString fileName =
		QFileDialog::getSaveFileName(this,
			tr("Save File"),
			QDir::currentPath(),
			tr("nonogram (*.nonogram)"));
	qDebug() << fileName;
	if (fileName.isEmpty()) return;
	setCurrentFileName(fileName);
	saveFile();
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

void MainWindow::on_actionAbout_triggered()
{
	QString textAbout = "Program to create and solve nonograms.<br>"
			"<a href=\"https://ololuki.pl\">ololuki.pl</a><br>"
			"<a href=\"https://github.com/ololuki/nonograms\">GitHub</a>";
	QMessageBox msgBox;
	msgBox.setWindowTitle("About nonograms");
	msgBox.setTextFormat(Qt::RichText);
	msgBox.setText(textAbout);
	msgBox.exec();	
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::setCurrentFileName(const QString &pathAndName)
{
	currentFileName = pathAndName;
	isFileNameSet = true;
}

void MainWindow::saveFile()
{
	FileWriter *writer = new NonogramFileWriter();
	writer->setField(field);
	if (writer->write(currentFileName.toStdString()))
	{
		ui->statusBar->showMessage(QString("Saved file: \"%1\"").arg(currentFileName));
	} else {
		QMessageBox::critical(this,
			"File Write Error",
			"Can not write to file.");
	}
	delete writer;
}

bool MainWindow::abandonChangesOrSavePrompt()
{
	auto answer = QMessageBox::question(this,
		"Unsaved changes",
		"Do you want to save changes?",
		QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel));
	if (answer == QMessageBox::Yes)
	{
		on_actionSave_as_triggered();
		
	} else if (answer == QMessageBox::Cancel) {
		return false;
	}
	return true;
}

void MainWindow::recreateField(size_t width, size_t height)
{
	field.reset(new WholeFieldImpl(width, height));
	ui->drawingArea->setField(field);
	ui->columnsDescription->setField(field);
	ui->rowsDescription->setField(field);
}

void MainWindow::replaceField(std::shared_ptr<WholeField> newField)
{
	if (newField == nullptr)
	{
		qDebug() << "null ptr";
		return;
	}
	field = newField;
	ui->drawingArea->setField(field);
	ui->columnsDescription->setField(field);
	ui->rowsDescription->setField(field);
	field->dataChanged();
}
