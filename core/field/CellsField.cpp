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
#include "CellsField.h"
#include <QDebug>


CellsField::CellsField(int width, int height) : array(width, height)
{
	qDebug() << "CellsField width height c-tor";
}

/// Build CellsField based on list of rows
/// This could be used in tests to make field from strings
/// representing rows of nonogram
CellsField::CellsField(std::initializer_list<LineOfCells> rows) : array(0, 0)
{
	if(rows.size() > 0)
	{
		int height = static_cast<int>(rows.size());
		int width = rows.begin()->size();
		array = ArrayOfCells(width, height);
		int lineNumber = 0;
		bool isOk = true; // true if all rows has same length
		for (auto row : rows)
		{
			if (row.size() == width)
			{
				setLineOfCells(row, lineNumber, Orientation::HORIZONTAL);
				++lineNumber;
			}
			else
			{
				// error, revert changes and make empty array
				isOk = false;
				break;
			}
		}
		if (isOk == false)
		{
			array = ArrayOfCells(0, 0);
		}
	}
}

CellsField& CellsField::operator=(CellsField&& field)
{
	array = std::move(field.array);
	return *this;
}

CellsField::~CellsField()
{
	qDebug() << "CellsField d-tor";
}

bool CellsField::areSolvedCellsEqual(const CellsField& other) const
{
	return array.areSolvedCellsEqual(other.array);
}

const Cell& CellsField::getCell(AddressOfCell address) const
{
	int x = address.getX();
	int y = address.getY();
	return array.getPixelAt(x, y);
}

void CellsField::setCell(Cell cell)
{
	if (cell.getAddress().isValid())
	{
		int x = cell.getAddress().getX();
		int y = cell.getAddress().getY();
		if (array(x, y) != cell)
		{
			array(x, y) = cell;
		}
	}
}

LineOfCells CellsField::getLineOfCells(int lineNumber, Orientation orientation) const
{
	NVector<Cell> line = NVector<Cell>();
	int lineLength;
	switch(orientation)
	{
	case Orientation::HORIZONTAL:
		lineLength = getWidth();
		break;
	case Orientation::VERTICAL:
		lineLength = getHeight();
		break;
	}
	for (int i = 0; i < lineLength; i++)
	{
		switch(orientation)
		{
		case Orientation::HORIZONTAL:
			line.push_back(getCell(AddressOfCell(i, lineNumber)));
			break;
		case Orientation::VERTICAL:
			line.push_back(getCell(AddressOfCell(lineNumber, i)));
			break;
		}
	}
	return line;
}

/// Set LineOfCells - this line should have cells with valid AddressOfCell
/// Use it only with lines taken from getLineOfCells or made using Cells
/// with valid Addresses
void CellsField::setLineOfCells(LineOfCells lineOfCells)
{
	for (int i = 0; i < lineOfCells.size(); i++)
	{
		setCell(lineOfCells[i]);
	}
}

/// Set LineOfCells - ignore AddressOfCell in LineOfCells and
/// replace it with valid Address based on given lineNumber
/// and orientation
void CellsField::setLineOfCells(LineOfCells lineOfCells,
                                int lineNumber,
                                Orientation orientation)
{
	for (int i = 0; i < lineOfCells.size(); i++)
	{
		if (orientation == Orientation::HORIZONTAL)
		{
			setCell(Cell(AddressOfCell{i, lineNumber},
			             lineOfCells[i].getSign()));
		}
		else if (orientation == Orientation::VERTICAL)
		{
			setCell(Cell(AddressOfCell{lineNumber, i},
			             lineOfCells[i].getSign()));
		}
	}
}
