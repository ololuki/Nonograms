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
#include "WholeFieldModel.h"


WholeFieldModel::WholeFieldModel(int width, int height)
	: width(width),
	  height(height)
{
	cellsField = std::make_shared<CellsFieldModel>(width, height);
	columnsHintsField = std::make_shared<HintsFieldModel>(width, Orientation::VERTICAL);
	rowsHintsField = std::make_shared<HintsFieldModel>(height, Orientation::HORIZONTAL);
}

WholeFieldModel::~WholeFieldModel()
{
}

int WholeFieldModel::getWidth() const
{
	return width;
}

int WholeFieldModel::getHeight() const
{
	return height;
}

std::shared_ptr<CellsFieldModel> WholeFieldModel::cells()
{
	return cellsField;
}

std::shared_ptr<HintsFieldModel> WholeFieldModel::columnsHints()
{
	return columnsHintsField;
}

std::shared_ptr<HintsFieldModel> WholeFieldModel::rowsHints()
{
	return rowsHintsField;
}

void WholeFieldModel::clearDrawingArea()
{
	for (int i = 0; i < getWidth(); i++)
	{
		for (int j = 0; j < getHeight(); j++)
		{
			cells()->setCell(Cell(AddressOfCell(i, j)));
		}
	}
}

void WholeFieldModel::clearBlocksDescription()
{
	// TODO
}

WholeField WholeFieldModel::getWholeField()
{
	return WholeField(cellsField->getCellsField(),
	                  columnsHintsField->getHintsField(),
	                  rowsHintsField->getHintsField());
}

void WholeFieldModel::setWholeField(const WholeField& field)
{
	cellsField->setCellsField(field.cells());
	columnsHintsField->setHintsField(field.columnsHints());
	rowsHintsField->setHintsField(field.rowsHints());
}
