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
#ifndef ABSTRACTCELLSCONTROLLER_H
#define ABSTRACTCELLSCONTROLLER_H

#include "field/WholeFieldModel.h"
#include "widgets/CellsView.h"
#include "action/CellAction.h"


class AbstractCellsController : public QObject
{
	Q_OBJECT
public:
	AbstractCellsController(std::shared_ptr<CellsFieldModel> newField, CellsView *cellsView);
	~AbstractCellsController() override;

private slots:
	virtual void onAction(CellAction action, AddressOfCell address) = 0;

protected:
	std::shared_ptr<CellsFieldModel> field;

private:
	CellsView *cellsView;
};

#endif // ABSTRACTCELLSCONTROLLER_H
