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
	fieldController = std::make_shared<FieldController>(ui->drawingArea, ui->columnsDescription, ui->rowsDescription);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionNew_triggered()
{
	fieldController->onNew();
}

void MainWindow::on_actionOpen_triggered()
{
	fieldController->onOpen();
}

void MainWindow::on_actionSave_as_triggered()
{
	fieldController->onSaveAs();
}

void MainWindow::on_actionAdd_blocks_triggered()
{
	fieldController->addDummyBlock();
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
