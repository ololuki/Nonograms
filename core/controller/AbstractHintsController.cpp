/**********************************************************************
 * Copyright (C) 2017 - 2022 Ololuki
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
#include "AbstractHintsController.h"
#include "widgets/HintsView.h"


AbstractHintsController::AbstractHintsController(std::shared_ptr<HintsFieldModel> field, HintsView *hintsView)
	: field(field)
{
	this->hintsView = hintsView;
	this->hintsView->setField(field);

	// signals from HintsView to this controller
	connect(
		hintsView,
		static_cast<void (HintsView::*)(HintAction, AddressOfHint)>(&HintsView::action),
		this,
		static_cast<void (AbstractHintsController::*)(HintAction, AddressOfHint)>(&AbstractHintsController::onAction)
	);
	connect(
		hintsView,
		static_cast<void (HintsView::*)(HintAction, Hint)>(&HintsView::action),
		this,
		static_cast<void (AbstractHintsController::*)(HintAction, Hint)>(&AbstractHintsController::onAction)
	);

	// signals from this controller to HintsView
	connect(
		this,
		&AbstractHintsController::showInsertingButtonBefore,
		hintsView,
		&HintsView::onShowInsertingButtonBefore
	);
	connect(
		this,
		&AbstractHintsController::showHintEditingBox,
		hintsView,
		&HintsView::onShowHintEditingBox
	);
}
