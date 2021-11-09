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
#include "FieldController.h"
#include "SizeDialog.h"
#include <QDebug>
#include "controller/EditableCellsController.h"
#include "controller/EditableHintsController.h"
#include "controller/ReadOnlyCellsController.h"
#include "controller/ReadOnlyHintsController.h"
#include "solver/field/DeductiveFieldSolver.h"


FieldController::FieldController(CellsView *cellsView, HintsView *columnsHintsView, HintsView *rowsHintsView)
{
	// create initial field
	field.reset(new WholeFieldModel(14, 10));
	
	this->cellsView = cellsView;
	this->columnsHintsView = columnsHintsView;
	this->rowsHintsView = rowsHintsView;
	
	cellsController = std::make_unique<EditableCellsController>(field->cells(), this->cellsView);
	columnsHintsController = std::make_unique<ReadOnlyHintsController>(field->columnsHints(), this->columnsHintsView);
	rowsHintsController = std::make_unique<ReadOnlyHintsController>(field->rowsHints(), this->rowsHintsView);
	
	fileManager = std::make_unique<FileManager>(field->getWholeField());
	
	qRegisterMetaType<Cell>();
	qRegisterMetaType<WholeField>();
	qRegisterMetaType<std::shared_ptr<AbstractFieldSolver>>();
	
	connect(&solverWorker, &SolverWorker::cellChanged, static_cast<const CellsFieldModel*>(this->field->cells().get()), &CellsFieldModel::setCell);
	connect(this, &FieldController::solve, &solverWorker, &SolverWorker::solve);
	connect(this, &FieldController::setFieldSolver, &solverWorker, &SolverWorker::setFieldSolver);
	connect(&solverWorker, &SolverWorker::isSolvingChanged, this, &FieldController::isSolvingChanged);
	connect(this, &FieldController::stopWorker, &solverWorker, &SolverWorker::stop);
	thread.start();
	
	solverWorker.moveToThread(&thread);
}

FieldController::~FieldController()
{
	emit stopWorker();
	thread.quit();
	thread.wait();
}

void FieldController::onNew()
{
	if (!fileManager->abandonChangesOrSavePrompt(field->getWholeField()))
		return;
	//fileManager->tryToSaveChanges(&isSavedOrAbandoned, &statusLog);
	//if (!isSavedOrAbandoned) return;
	
	SizeDialog *d = new SizeDialog();
	bool isConfirmed = d->exec();
	int width = d->getWidth();
	int height = d->getHeight();
	delete d;
	if (isConfirmed)
	{
		field->setWholeField(WholeField(width, height));
		fileManager->setNewCreatedField(field->getWholeField());
	}
}

void FieldController::onOpen()
{
	if (!fileManager->abandonChangesOrSavePrompt(field->getWholeField()))
		return;
	if (fileManager->tryOpenAnotherFile())
	{
		field->setWholeField(fileManager->getField());
	}
}

void FieldController::onSaveAs()
{
	fileManager->trySaveAs(field->getWholeField());
}

///
/// \brief Set drawing mode.
/// Changes controllers behavior - drawing cells and defining hints
/// could be enabled or disabled based on DrawingMode.
/// \param drawingMode - new mode to set
///
void FieldController::setDrawingMode(DrawingMode drawingMode)
{
	this->drawingMode = drawingMode;

	if (drawingMode == DrawingMode::FreeDrawing || drawingMode == DrawingMode::ManualSolving)
	{
		cellsController = std::make_unique<EditableCellsController>(field->cells(), this->cellsView);
	}
	else
	{
		cellsController = std::make_unique<ReadOnlyCellsController>(field->cells(), this->cellsView);
	}

	if (drawingMode == DrawingMode::FieldDefining)
	{
		columnsHintsController = std::make_unique<EditableHintsController>(field->columnsHints(), this->columnsHintsView);
		rowsHintsController = std::make_unique<EditableHintsController>(field->rowsHints(), this->rowsHintsView);
	}
	else
	{
		columnsHintsController = std::make_unique<ReadOnlyHintsController>(field->columnsHints(), this->columnsHintsView);
		rowsHintsController = std::make_unique<ReadOnlyHintsController>(field->rowsHints(), this->rowsHintsView);
	}
}

///
/// \brief Used when user clicks "Solve" button.
/// \param start - if true button starts solving
/// if false stops solving
///
void FieldController::onSolve(bool start)
{
	if (start)
	{
		// TODO: choose appropriate type of solver here
		emit setFieldSolver(std::make_shared<DeductiveFieldSolver>());
		emit solve(field->getWholeField());
	}
	else
		emit stopWorker();
}
