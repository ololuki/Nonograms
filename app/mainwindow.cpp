/**********************************************************************
 * Copyright (C) 2017 Ololuki
 * https://ololuki.pl
 * 
 * This file is part of Nonograms
 * https://github.com/ololuki/nonograms
 * 
 * Nonograms is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Nonograms is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Nonograms.  If not, see <http://www.gnu.org/licenses/>.
 *********************************************************************/
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
	
	// grouping checkable menu actions into radio buttons
	QActionGroup* group = new QActionGroup(this);
	ui->actionFree_drawing->setActionGroup(group);
	ui->actionField_defining->setActionGroup(group);
	ui->actionHuman_solving->setActionGroup(group);
	ui->actionAuto_solving->setActionGroup(group);
	
	fieldController = std::make_shared<FieldController>(ui->cells, ui->columnsHints, ui->rowsHints);
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
