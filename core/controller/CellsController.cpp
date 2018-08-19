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
#include "CellsController.h"
#include <QDebug>


CellsController::CellsController(std::shared_ptr<CellsField> newField, CellsView *cellsView)
	: field(newField)
{
	qDebug() << "DrawingAreaController constructor";
	this->cellsView = cellsView;
	this->cellsView->setField(field);
	
	connect(
		this->cellsView,
		&CellsView::action,
		this,
		&CellsController::onAction
	);
}

CellsController::~CellsController()
{
	qDebug() << "DrawingAreaController destructor";
	disconnect(this->cellsView, &CellsView::action, this, &CellsController::onAction);
}

void CellsController::replaceField(std::shared_ptr<CellsField> newField)
{
	this->field = newField;
	cellsView->setField(field);
}

void CellsController::onAction(CellAction action, AddressOfCell address)
{
	Cell cell(address);
	switch(action)
	{
	case CellAction::MakeFilledBlack:
		cell.makeFilledBlack();
		break;
	case CellAction::MakeDot:
		cell.makeDot();
		break;
	case CellAction::MakeEmpty:
		cell.makeEmpty();
		break;
	default:
		break;
	}
	field->setCell(cell);
}
