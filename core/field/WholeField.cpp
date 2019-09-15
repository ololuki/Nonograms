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
#include "WholeField.h"
#include <QDebug>


WholeField::WholeField()
  : WholeField(0, 0)
{
	qDebug() << "WholeField default c-tor";
}

WholeField::WholeField(int width, int height)
  : width(width),
    height(height),
    cellsField(width, height),
    columnsHintsField(width, Orientation::VERTICAL),
    rowsHintsField(height, Orientation::HORIZONTAL)

{
	qDebug() << "WholeField width height c-tor";
}

WholeField::WholeField(CellsField cells, HintsField columns, HintsField rows)
  : width(cells.getWidth()),
    height(cells.getHeight()),
    cellsField(cells),
    columnsHintsField(columns),
    rowsHintsField(rows)
{
	qDebug() << "WholeField cells, columns, rows c-tor";
}

WholeField::WholeField(const WholeField &field)
  : width(field.width),
    height(field.height),
    cellsField(field.cellsField),
    columnsHintsField(field.columnsHintsField),
    rowsHintsField(field.rowsHintsField)
{
	qDebug() << "WholeField copy c-tor";
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
