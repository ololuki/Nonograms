/**********************************************************************
 * Copyright (C) 2017-2018 Ololuki
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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "controller/FieldController.h"


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	
private slots:
	void on_actionNew_triggered();
	void on_actionOpen_triggered();
	void on_actionSave_as_triggered();
	
	void on_actionFree_drawing_triggered();
	void on_actionField_defining_triggered();
	void on_actionManual_solving_triggered();
	void on_actionAuto_solving_triggered();
	void on_actionAuto_solving_brute_force_triggered();
	void on_actionSolve_triggered();
	
	void on_actionAdd_blocks_triggered();
	
	void on_actionAbout_triggered();
	void on_actionAbout_Qt_triggered();
	
private:
	std::shared_ptr<Ui::MainWindow> ui;
	std::shared_ptr<FieldController> fieldController;
	
	const QString textStopSolving = "Stop";
	const QString textSolve = "Solve";
};

#endif // MAINWINDOW_H
