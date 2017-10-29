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


BlocksDescriptionController::BlocksDescriptionController(std::shared_ptr<BlocksDescriptionField> field, HintsView *hintsView)
	: field(field)
{
	this->hintsView = hintsView;
	this->hintsView->setField(field);
	
	connect(
		hintsView,
		static_cast<void (HintsView::*)(HintAction, AddressOnBlocksDescription)>(&HintsView::action),
		this,
		static_cast<void (BlocksDescriptionController::*)(HintAction, AddressOnBlocksDescription)>(&BlocksDescriptionController::onAction)
	);
	connect(
		hintsView,
		static_cast<void (HintsView::*)(HintAction, BlockDescription)>(&HintsView::action),
		this,
		static_cast<void (BlocksDescriptionController::*)(HintAction, BlockDescription)>(&BlocksDescriptionController::onAction)
	);
	
	connect(
		this,
		&BlocksDescriptionController::showInsertingButtonBefore,
		hintsView,
		&HintsView::showInsertingButtonBefore
	);
	connect(
		this,
		&BlocksDescriptionController::showDescriptionEditingBox,
		hintsView,
		&HintsView::showDescriptionEditingBox
	);
}

BlocksDescriptionController::~BlocksDescriptionController()
{
	
}

void BlocksDescriptionController::replaceField(std::shared_ptr<BlocksDescriptionField> newField)
{
	this->field = newField;
	hintsView->setField(field);
}

void BlocksDescriptionController::onAction(HintAction action, AddressOnBlocksDescription address)
{
	switch(action)
	{
	case HintAction::InsertingButtonHover:
		showInsertingButtonBefore(address);
		break;
	case HintAction::ShowEditBox:
		showDescriptionEditingBox(address);
		break;
	case HintAction::HintInsertBefore:
		onHintInsertBefore(address);
		break;
	case HintAction::HintDelete:
		field->deleteDescription(BlockDescription(address, 0));
		break;
	default:
		break;
	}
}

void BlocksDescriptionController::onAction(HintAction action, BlockDescription blockDescription)
{
	switch(action)
	{
	case HintAction::HintUpdate:
		field->updateBlockDescription(blockDescription);
		break;
	default:
		break;
	}
}

void BlocksDescriptionController::onHintInsertBefore(AddressOnBlocksDescription address)
{
	int line = address.getLine();
	int count = address.getCount();
	if (count < field->numberOfBlocksInLine(line))
	{
		field->insertDescriptionBefore(BlockDescription(address, 0));
	}
	else if (count == field->numberOfBlocksInLine(line))
	{
		field->addDescriptionAtEnd(BlockDescription(address, 0));
	}
}
