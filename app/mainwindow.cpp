#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field/WholeFieldImpl.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	WholeField *field = new WholeFieldImpl(14, 10);
	
	ui->setupUi(this);
	
	ui->drawingArea->setField(field);
}

MainWindow::~MainWindow()
{
	delete ui;
}
