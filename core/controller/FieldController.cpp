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
#include "FieldController.h"
#include "SizeDialog.h"
#include <QDebug>
#include "../solver/line/CoveringBlocksSolver.h"


FieldController::FieldController(CellsView *cellsView, HintsView *columnsHintsView, HintsView *rowsHintsView)
{
	// create initial field
	field.reset(new WholeFieldModel(14, 10));
	
	this->cellsView = cellsView;
	this->columnsHintsView = columnsHintsView;
	this->rowsHintsView = rowsHintsView;
	
	cellsController = std::make_shared<CellsController>(field->cells(), this->cellsView);
	columnsHintsController = std::make_shared<HintsController>(field->columnsHints(), this->columnsHintsView);
	rowsHintsController = std::make_shared<HintsController>(field->rowsHints(), this->rowsHintsView);
	
	fileManager = std::make_shared<FileManager>(field);
	
	qRegisterMetaType<Cell>();
	qRegisterMetaType<std::shared_ptr</*const*/ WholeFieldModel>>();
	
	connect(&solverWorker, &SolverWorker::cellChanged, static_cast<const CellsFieldModel*>(this->field->cells().get()), &CellsFieldModel::setCell);
	connect(this, &FieldController::solve, &solverWorker, &SolverWorker::solve);
	connect(&solverWorker, &SolverWorker::isSolvingChanged, this, &FieldController::isSolvingChanged);
	connect(this, &FieldController::stopWorker, &solverWorker, &SolverWorker::stop);
	thread.start();
	
	std::shared_ptr<AbstractLineSolver> solver = std::make_shared<CoveringBlocksSolver>();
	solverWorker.addLineSolver(solver);
	
	solverWorker.moveToThread(&thread);
}

FieldController::~FieldController()
{
	emit stopWorker();
	thread.quit();
	thread.wait();
}

void FieldController::addDummyBlock()
{
	if (field->getWidth() < 3 || field->getHeight() < 8) return;
	field->cells()->setCell(Cell(AddressOfCell(2,5), cellSign::SGN_FILL_BLACK));
	field->cells()->setCell(Cell(AddressOfCell(2,7), cellSign::SGN_FILL_BLACK));
	field->columnsHints()->updateHint(Hint(AddressOfHint(Orientation::VERTICAL, 2, 0), 1));
	field->columnsHints()->addHintAtEnd(Hint(AddressOfHint(Orientation::VERTICAL, 2, 1), 1));
	field->rowsHints()->updateHint(Hint(AddressOfHint(Orientation::HORIZONTAL, 5, 0), 1));
	field->rowsHints()->updateHint(Hint(AddressOfHint(Orientation::HORIZONTAL, 7, 0), 1));
}

void FieldController::replaceField(int width, int height)
{
	std::shared_ptr<WholeFieldModel> newField = std::make_shared<WholeFieldModel>(width, height);
	replaceField(newField);
}

void FieldController::replaceField(std::shared_ptr<WholeFieldModel> newField)
{
	if (newField == nullptr)
	{
		qDebug() << "null ptr";
		return;
	}
	field = newField;
	
	cellsController->replaceField(field->cells());
	columnsHintsController->replaceField(field->columnsHints());
	rowsHintsController->replaceField(field->rowsHints());
	
	connect(&solverWorker, &SolverWorker::cellChanged, static_cast<const CellsFieldModel*>(this->field->cells().get()), &CellsFieldModel::setCell);
}

void FieldController::onNew()
{
	if (!fileManager->abandonChangesOrSavePrompt(field)) return;
	//fileManager->tryToSaveChanges(&isSavedOrAbandoned, &statusLog);
	//if (!isSavedOrAbandoned) return;
	
	SizeDialog *d = new SizeDialog();
	bool isConfirmed = d->exec();
	int width = d->getWidth();
	int height = d->getHeight();
	delete d;
	if (isConfirmed)
	{
		replaceField(width, height);
		fileManager->setNewCreatedField(field);
	}
}

void FieldController::onOpen()
{
	if (!fileManager->abandonChangesOrSavePrompt(field)) return;
	fileManager->tryOpenAnotherFile();
	replaceField(fileManager->getField());
}

void FieldController::onSaveAs()
{
	fileManager->trySaveAs(field);
}

///
/// \brief Used when user clicks "Solve" button.
/// \param start - if true button starts solving
/// if false stops solving
///
void FieldController::onSolve(bool start)
{
	if (start)
		emit solve(field);
	else
		emit stopWorker();
}
