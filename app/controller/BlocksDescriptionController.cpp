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
#include "BlocksDescriptionController.h"


BlocksDescriptionController::BlocksDescriptionController(std::shared_ptr<BlocksDescriptionField> field, ColumnsDescriptionView *columnsDescriptionView, RowsDescriptionView *rowsDescriptionView)
{
	connect(columnsDescriptionView, &ColumnsDescriptionView::insertingButtonHover, this, &BlocksDescriptionController::onInsertingButtonHover);
	//connect(rowsDescriptionView, &RowsDescriptionView::insertingButtonHover, this, &BlocksDescriptionController::onInsertingButtonHover);
	//connect(columnsDescriptionView, &ColumnsDescriptionView::descriptionEditingFinished, this, &BlocksDescriptionController::onDescriptionEditingFinished);
	
	connect(columnsDescriptionView, &ColumnsDescriptionView::insertingButtonBeforeAddressClicked, this, &BlocksDescriptionController::onInsertingButtonBeforeAddressClicked);
	
	connect(columnsDescriptionView, &ColumnsDescriptionView::blockDescriptionClicked, this, &BlocksDescriptionController::onBlockDescriptionClicked);
	
	connect(this, &BlocksDescriptionController::showInsertingButtonBefore, columnsDescriptionView, &ColumnsDescriptionView::showInsertingButtonBefore);
	
	connect(this, &BlocksDescriptionController::showDescriptionEditingBox, columnsDescriptionView, &ColumnsDescriptionView::showDescriptionEditingBox);
	
}

BlocksDescriptionController::~BlocksDescriptionController()
{
	
}

void BlocksDescriptionController::onInsertingButtonHover(AddressOnBlocksDescription address)
{
	showInsertingButtonBefore(address);
}

void BlocksDescriptionController::onDescriptionEditingFinished(BlockDescription blockDescription)
{
	
}

void BlocksDescriptionController::onInsertingButtonBeforeAddressClicked(AddressOnBlocksDescription address)
{
	
}

void BlocksDescriptionController::onBlockDescriptionClicked(AddressOnBlocksDescription address)
{
	
}
