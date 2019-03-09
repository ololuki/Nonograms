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
#include "WholeField.h"
#include <QDebug>


WholeField::WholeField(int width, int height)
	: width(width),
	  height(height)
{
	cellsField = std::make_shared<CellsFieldModel>(width, height);
	columnsHintsField = std::make_shared<HintsFieldModel>(width, Orientation::VERTICAL);
	rowsHintsField = std::make_shared<HintsFieldModel>(height, Orientation::HORIZONTAL);
	qDebug() << "WholeField width height c-tor";
}

WholeField::WholeField(const WholeField &field)
	: width(field.width),
	  height(field.height)
{
	cellsField = field.cellsField;
	columnsHintsField = field.columnsHintsField;
	rowsHintsField = field.rowsHintsField;
	qDebug() << "WholeField copy c-tor";
}

WholeField::~WholeField()
{
	qDebug() << "WholeField d-tor";
}

int WholeField::getWidth() const
{
	return width;
}

int WholeField::getHeight() const
{
	return height;
}

std::shared_ptr<CellsFieldModel> WholeField::cells()
{
	return cellsField;
}

std::shared_ptr<HintsFieldModel> WholeField::columnsHints()
{
	return columnsHintsField;
}

std::shared_ptr<HintsFieldModel> WholeField::rowsHints()
{
	return rowsHintsField;
}

void WholeField::clearDrawingArea()
{
	for (int i = 0; i < getWidth(); i++)
	{
		for (int j = 0; j < getHeight(); j++)
		{
			cells()->setCell(Cell(AddressOfCell(i, j)));
		}
	}
}

void WholeField::clearBlocksDescription()
{
	// TODO
}
