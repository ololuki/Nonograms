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
#ifndef FIELDCONTROLLER_H
#define FIELDCONTROLLER_H

#include "field/WholeField.h"
#include "widgets/DrawingAreaView.h"
#include "widgets/HintsView.h"
#include "controller/DrawingAreaController.h"
#include "controller/BlocksDescriptionController.h"
#include "file/FileManager.h"


class FieldController : public QObject
{
	Q_OBJECT
public:
	FieldController(DrawingAreaView *drawingAreaView, HintsView *columnsDescriptionView, HintsView *rowsDescriptionView);
	void addDummyBlock();
	
	void onNew();
	void onOpen();
	void onSaveAs();
private:
	void recreateField(int width, int height);
	void replaceField(std::shared_ptr<WholeField> newField);
	
	std::shared_ptr<WholeField> field;
	
	DrawingAreaView *drawingAreaView;
	HintsView *columnsDescriptionView;
	HintsView *rowsDescriptionView;
	
	std::shared_ptr<DrawingAreaController> drawingAreaController;
	std::shared_ptr<BlocksDescriptionController> columnsHintsController;
	std::shared_ptr<BlocksDescriptionController> rowsHintsController;
	std::shared_ptr<FileManager> fileManager;
};

#endif // FIELDCONTROLLER_H
