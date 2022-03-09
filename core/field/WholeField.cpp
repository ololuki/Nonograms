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
#include "WholeField.h"


WholeField::WholeField()
  : WholeField(0, 0)
{
}

WholeField::WholeField(int width, int height)
  : width(width),
    height(height),
    cellsField(width, height),
    columnsHintsField(width, Orientation::VERTICAL),
    rowsHintsField(height, Orientation::HORIZONTAL)
{
}

WholeField::WholeField(const CellsField& cells, const HintsField& columns, const HintsField& rows)
  : width(cells.getWidth()),
    height(cells.getHeight()),
    cellsField(cells),
    columnsHintsField(columns),
    rowsHintsField(rows)
{
}

WholeField::WholeField(CellsField&& cells, HintsField&& columns, HintsField&& rows)
  : width(cells.getWidth()),
    height(cells.getHeight()),
    cellsField(std::move(cells)),
    columnsHintsField(std::move(columns)),
    rowsHintsField(std::move(rows))
{
}

WholeField::WholeField(const WholeField &field)
  : width(field.width),
    height(field.height),
    cellsField(field.cellsField),
    columnsHintsField(field.columnsHintsField),
    rowsHintsField(field.rowsHintsField)
{
}

WholeField& WholeField::operator=(const WholeField& field)
{
	width = field.width;
	height = field.height;
	cellsField = field.cellsField;
	columnsHintsField = field.columnsHintsField;
	rowsHintsField = field.rowsHintsField;
	return *this;
}

WholeField& WholeField::operator=(WholeField&& field)
{
	width = field.width;
	height = field.height;
	cellsField = std::move(field.cellsField);
	columnsHintsField = std::move(field.columnsHintsField);
	rowsHintsField = std::move(field.rowsHintsField);
	return *this;
}

WholeField::~WholeField()
{
}

bool WholeField::operator==(const WholeField& other) const
{
	return cellsField == other.cellsField
	        && columnsHintsField == other.columnsHintsField
	        && rowsHintsField == other.rowsHintsField;
}

bool WholeField::operator!=(const WholeField& other) const
{
	return cellsField != other.cellsField
	        || columnsHintsField != other.columnsHintsField
	        || rowsHintsField != other.rowsHintsField;
}

int WholeField::getWidth() const
{
	return width;
}

int WholeField::getHeight() const
{
	return height;
}

CellsField& WholeField::cells()
{
	return cellsField;
}

HintsField& WholeField::columnsHints()
{
	return columnsHintsField;
}

HintsField& WholeField::rowsHints()
{
	return rowsHintsField;
}

const CellsField& WholeField::cells() const
{
	return cellsField;
}

const HintsField& WholeField::columnsHints() const
{
	return columnsHintsField;
}

const HintsField& WholeField::rowsHints() const
{
	return rowsHintsField;
}

void WholeField::clearDrawingArea()
{
	for (int i = 0; i < getWidth(); i++)
	{
		for (int j = 0; j < getHeight(); j++)
		{
			cellsField.setCell(Cell(AddressOfCell(i, j)));
		}
	}
}

void WholeField::clearBlocksDescription()
{
	// TODO
}
