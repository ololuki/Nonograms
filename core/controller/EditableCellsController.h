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
#ifndef EDITABLECELLSCONTROLLER_H
#define EDITABLECELLSCONTROLLER_H

#include "AbstractCellsController.h"

///
/// Editable controller.
/// Handles user input and allow modifications.
///
class EditableCellsController : public AbstractCellsController
{
public:
	EditableCellsController(std::shared_ptr<CellsFieldModel> newField, CellsView *view);
	~EditableCellsController() override = default;

private slots:
	void onAction(CellAction action, AddressOfCell address) override;
};

#endif // EDITABLECELLSCONTROLLER_H
