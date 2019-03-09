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
#ifndef CELLSCONTROLLER_H
#define CELLSCONTROLLER_H

#include "field/WholeFieldModel.h"
#include "widgets/CellsView.h"
#include "action/CellAction.h"


class CellsController : public QObject
{
	Q_OBJECT
public:
	CellsController(std::shared_ptr<CellsFieldModel> newField, CellsView *cellsView);
	~CellsController();
	void replaceField(std::shared_ptr<CellsFieldModel> newField);
	
private slots:
	void onAction(CellAction action, AddressOfCell address);
	
private:
	std::shared_ptr<CellsFieldModel> field;
	CellsView *cellsView;
};

#endif // CELLSCONTROLLER_H
