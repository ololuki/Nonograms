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
#include "HintsController.h"
#include "field/HintsFieldModel.h"
#include "widgets/HintsView.h"


HintsController::HintsController(std::shared_ptr<HintsFieldModel> field, HintsView *hintsView)
	: field(field)
{
	this->hintsView = hintsView;
	this->hintsView->setField(field);

	connect(
		hintsView,
		static_cast<void (HintsView::*)(HintAction, AddressOfHint)>(&HintsView::action),
		this,
		static_cast<void (HintsController::*)(HintAction, AddressOfHint)>(&HintsController::onAction)
	);
	connect(
		hintsView,
		static_cast<void (HintsView::*)(HintAction, Hint)>(&HintsView::action),
		this,
		static_cast<void (HintsController::*)(HintAction, Hint)>(&HintsController::onAction)
	);

	connect(
		this,
		&HintsController::showInsertingButtonBefore,
		hintsView,
		&HintsView::onShowInsertingButtonBefore
	);
	connect(
		this,
		&HintsController::showHintEditingBox,
		hintsView,
		&HintsView::onShowHintEditingBox
	);
}

void HintsController::onAction(HintAction action, AddressOfHint address)
{
	switch(action)
	{
	case HintAction::InsertingButtonHover:
		showInsertingButtonBefore(address);
		break;
	case HintAction::ShowEditBox:
		showHintEditingBox(address);
		break;
	case HintAction::HintInsertBefore:
		onHintInsertBefore(address);
		break;
	case HintAction::HintDelete:
		field->deleteHint(Hint(address, 0));
		break;
	default:
		break;
	}
}

void HintsController::onAction(HintAction action, Hint hint)
{
	switch(action)
	{
	case HintAction::HintUpdate:
		field->updateHint(hint);
		break;
	default:
		break;
	}
}

void HintsController::onHintInsertBefore(AddressOfHint address)
{
	int line = address.getLine();
	int count = address.getCount();
	if (count < field->numberOfBlocksInLine(line))
	{
		field->insertHintBefore(Hint(address, 0));
	}
	else if (count == field->numberOfBlocksInLine(line))
	{
		field->addHintAtEnd(Hint(address, 0));
	}
}
