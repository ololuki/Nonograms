/**********************************************************************
 * Copyright (C) 2021 Ololuki
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
#include "EditableHintsController.h"
#include "field/HintsFieldModel.h"


EditableHintsController::EditableHintsController(
        std::shared_ptr<HintsFieldModel> newField,
        HintsView* hintsView)
    : AbstractHintsController(newField, hintsView)
{
}

void EditableHintsController::onAction(HintAction action, AddressOfHint address)
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

void EditableHintsController::onAction(HintAction action, Hint hint)
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

/// Used when inserting button is clicked.
/// Inserts new Hint in place of address.
void EditableHintsController::onHintInsertBefore(AddressOfHint address)
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
