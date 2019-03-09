/**********************************************************************
 * Copyright (C) 2017 - 2019 Ololuki
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
#include <QDebug>


WholeFieldModel::WholeFieldModel(int width, int height)
	: width(width),
	  height(height)
{
	cellsField = std::make_shared<CellsFieldModel>(width, height);
	columnsHintsField = std::make_shared<HintsFieldModel>(width, Orientation::VERTICAL);
	rowsHintsField = std::make_shared<HintsFieldModel>(height, Orientation::HORIZONTAL);
	qDebug() << "WholeFieldModel width height c-tor";
}

WholeFieldModel::WholeFieldModel(const WholeFieldModel &field)
	: width(field.width),
	  height(field.height)
{
	cellsField = field.cellsField;
	columnsHintsField = field.columnsHintsField;
	rowsHintsField = field.rowsHintsField;
	qDebug() << "WholeFieldModel copy c-tor";
}

WholeFieldModel::~WholeFieldModel()
{
	qDebug() << "WholeFieldModel d-tor";
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
