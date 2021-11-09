/**********************************************************************
 * Copyright (C) 2017 - 2021 Ololuki
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
#ifndef FIELDCONTROLLER_H
#define FIELDCONTROLLER_H

#include "field/WholeFieldModel.h"
#include "widgets/CellsView.h"
#include "widgets/HintsView.h"
#include "controller/AbstractCellsController.h"
#include "controller/AbstractHintsController.h"
#include "file/FileManager.h"
#include "../solver/SolverWorker.h"
#include "DrawingMode.h"

#include <QThread>


class FieldController : public QObject
{
	Q_OBJECT
public:
	FieldController(CellsView *cellsView, HintsView *columnsHintsView, HintsView *rowsHintsView);
	~FieldController();
	void addDummyBlock();
	
	void onNew();
	void onOpen();
	void onSaveAs();
	
	void setDrawingMode(DrawingMode drawingMode);
	void onSolve(bool start);
	
signals:
	/// emited to worker to set appropriate solver
	void setFieldSolver(std::shared_ptr<AbstractFieldSolver> solver);
	/// emited to worker to start solving
	void solve(WholeField wholeField);
	/// emited by worker when state (is solving or stopped) changed
	void isSolvingChanged(bool isSolving);
	/// emited to worker to stop jobs
	void stopWorker();
	
private:
	std::unique_ptr<WholeFieldModel> field;
	
	CellsView *cellsView;
	HintsView *columnsHintsView;
	HintsView *rowsHintsView;

	DrawingMode drawingMode;

	std::unique_ptr<AbstractCellsController> cellsController;
	std::unique_ptr<AbstractHintsController> columnsHintsController;
	std::unique_ptr<AbstractHintsController> rowsHintsController;
	std::unique_ptr<FileManager> fileManager;
	
	SolverWorker solverWorker;
	QThread thread;
};

#endif // FIELDCONTROLLER_H
