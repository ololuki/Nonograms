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
#include "DrawingAreaController.h"
#include <QDebug>


DrawingAreaController::DrawingAreaController(std::shared_ptr<DrawingAreaField> newField, DrawingAreaView *drawingAreaView)
	: field(newField)
{
	qDebug() << "DrawingAreaController constructor";
	this->drawingAreaView = drawingAreaView;
	this->drawingAreaView->setField(field);
	
	connect(
		drawingAreaView,
		&DrawingAreaView::action,
		this,
		&DrawingAreaController::onAction
	);
}

DrawingAreaController::~DrawingAreaController()
{
	qDebug() << "DrawingAreaController destructor";
	disconnect(drawingAreaView, &DrawingAreaView::action, this, &DrawingAreaController::onAction);
}

void DrawingAreaController::replaceField(std::shared_ptr<DrawingAreaField> newField)
{
	this->field = newField;
	drawingAreaView->setField(field);
}

void DrawingAreaController::onAction(CellAction action, AddressOnDrawingArea address)
{
	Pixel pixel(address);
	switch(action)
	{
	case CellAction::MakeFilledBlack:
		pixel.makeFilledBlack();
		break;
	case CellAction::MakeDot:
		pixel.makeDot();
		break;
	case CellAction::MakeEmpty:
		pixel.makeEmpty();
		break;
	default:
		break;
	}
	field->setPixel(pixel);
}
