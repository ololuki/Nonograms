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
#include "LineOfCells.h"


///
/// \brief Makes invalid, empty vector of Cells.
/// Used to support data driven tests.
///
LineOfCells::LineOfCells()
{
	
}

///
/// \brief Makes valid line of Cells from String.
/// One char in str is one Cell. Chars are defined in CellSign.
/// Used mainly for tests.
/// \param str - line as string
///
LineOfCells::LineOfCells(QString str)
{
	for (int i = 0; i < str.size(); i++)
	{
		cells.push_back(Cell(str[i].toLatin1()));
	}
}

LineOfCells::LineOfCells(NVector<Cell> vectorToCopy)
	: cells(vectorToCopy)
{
}

int LineOfCells::size() const
{
	return cells.size();
}

Cell &LineOfCells::at(int cellNumber)
{
	return cells.operator[](cellNumber);
}

const Cell &LineOfCells::at(int cellNumber) const
{
	return cells.operator[](cellNumber);
}

Cell &LineOfCells::operator[](int cellNumber)
{
	return cells.operator[](cellNumber);
}

///
/// \brief Compare if LineOfCells have the same lenght and
/// contains the same CellSigns.
/// AddressOfCells are ignored.
/// \param other
/// \return true if CellSigns are equal in both LineOfCells.
///
bool LineOfCells::operator==(const LineOfCells& other) const
{
	if (size() != other.size())
		return false;
	for (int i = 0; i < size(); i++)
	{
		if (at(i) != other.at(i))
			return false;
	}
	return true;
}

bool LineOfCells::operator!=(const LineOfCells& other) const
{
	return !operator==(other);
}
