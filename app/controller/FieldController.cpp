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
#include "FieldController.h"
#include "field/WholeFieldImpl.h"
#include "SizeDialog.h"
#include <QDebug>


FieldController::FieldController(DrawingAreaView *drawingAreaView, ColumnsDescriptionView *columnsDescriptionView, RowsDescriptionView *rowsDescriptionView)
{
	// create initial field
	field.reset(new WholeFieldImpl(14, 10));
	
	this->drawingAreaView = drawingAreaView;
	drawingAreaController = std::make_shared<DrawingAreaController>(field->drawingArea(), drawingAreaView);
	
	this->columnsDescriptionView = columnsDescriptionView;
	columnsDescriptionView->setField(field->columnsDescription());
	
	this->rowsDescriptionView = rowsDescriptionView;
	rowsDescriptionView->setField(field->rowsDescription());
	
	columnsDescriptionController = std::make_shared<BlocksDescriptionController>(field->columnsDescription(), columnsDescriptionView, rowsDescriptionView);
	
	fileController = std::make_shared<FileController>(field);
}

void FieldController::addDummyBlock()
{
	if (field->getWidth() < 3 || field->getHeight() < 8) return;
	field->drawingArea()->setPixel(Pixel(AddressOnDrawingArea(2,5), pixelSign::SGN_FILL_BLACK));
	field->drawingArea()->setPixel(Pixel(AddressOnDrawingArea(2,7), pixelSign::SGN_FILL_BLACK));
	field->columnsDescription()->updateBlockDescription(BlockDescription(AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, 2, 0), 1));
	field->columnsDescription()->addDescriptionAtEnd(BlockDescription(AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, 2, 1), 1));
	field->rowsDescription()->updateBlockDescription(BlockDescription(AddressOnBlocksDescription(AddressOnBlocksDescription::HORIZONTAL, 5, 0), 1));
	field->rowsDescription()->updateBlockDescription(BlockDescription(AddressOnBlocksDescription(AddressOnBlocksDescription::HORIZONTAL, 7, 0), 1));
}

void FieldController::recreateField(size_t width, size_t height)
{
	field.reset(new WholeFieldImpl(width, height));
	drawingAreaController->replaceField(field->drawingArea());
	columnsDescriptionView->setField(field->columnsDescription());
	rowsDescriptionView->setField(field->rowsDescription());
}

void FieldController::replaceField(std::shared_ptr<WholeField> newField)
{
	if (newField == nullptr)
	{
		qDebug() << "null ptr";
		return;
	}
	field = newField;
	
	drawingAreaController->replaceField(field->drawingArea());
	
	columnsDescriptionView->setField(field->columnsDescription());
	rowsDescriptionView->setField(field->rowsDescription());
}

void FieldController::onNew()
{
	if (!fileController->abandonChangesOrSavePrompt(field)) return;
	//fileController->tryToSaveChanges(&isSavedOrAbandoned, &statusLog);
	//if (!isSavedOrAbandoned) return;
	
	SizeDialog *d = new SizeDialog();
	bool isConfirmed = d->exec();
	size_t width = d->getWidth();
	size_t height = d->getHeight();
	delete d;
	if (isConfirmed)
	{
		recreateField(width, height);
		fileController->setNewCreatedField(field);
	}
}

void FieldController::onOpen()
{
	if (!fileController->abandonChangesOrSavePrompt(field)) return;
	fileController->tryOpenAnotherFile();
	replaceField(fileController->getField());
}

void FieldController::onSaveAs()
{
	fileController->trySaveAs(field);
}
