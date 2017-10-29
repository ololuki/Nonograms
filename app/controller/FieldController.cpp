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
#include "SizeDialog.h"
#include <QDebug>


FieldController::FieldController(DrawingAreaView *drawingAreaView, HintsView *columnsDescriptionView, HintsView *rowsDescriptionView)
{
	// create initial field
	field.reset(new WholeField(14, 10));
	
	this->drawingAreaView = drawingAreaView;
	this->columnsDescriptionView = columnsDescriptionView;
	this->rowsDescriptionView = rowsDescriptionView;
	
	drawingAreaController = std::make_shared<DrawingAreaController>(field->drawingArea(), drawingAreaView);
	columnsHintsController = std::make_shared<BlocksDescriptionController>(field->columnsDescription(), columnsDescriptionView);
	rowsHintsController = std::make_shared<BlocksDescriptionController>(field->rowsDescription(), rowsDescriptionView);
	
	fileManager = std::make_shared<FileManager>(field);
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

void FieldController::recreateField(int width, int height)
{
	field.reset(new WholeField(width, height));
	drawingAreaController->replaceField(field->drawingArea());
	columnsHintsController->replaceField(field->columnsDescription());
	rowsHintsController->replaceField(field->rowsDescription());
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
	columnsHintsController->replaceField(field->columnsDescription());
	rowsHintsController->replaceField(field->rowsDescription());
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
		recreateField(width, height);
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
