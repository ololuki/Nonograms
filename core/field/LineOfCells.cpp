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
LineOfCells::LineOfCells(std::string str)
{
	cells.reserve(static_cast<int>(str.size()));
	for (size_t i = 0; i < str.size(); i++)
	{
		cells.emplace_back(str[i]);
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

Cell& LineOfCells::at(int cellNumber)
{
	return cells.at(cellNumber);
}

const Cell& LineOfCells::at(int cellNumber) const
{
	return cells.at(cellNumber);
}

Cell& LineOfCells::operator[](int cellNumber)
{
	return cells.operator[](cellNumber);
}

Cell& LineOfCells::front()
{
	return cells.front();
}

const Cell& LineOfCells::front() const
{
	return cells.front();
}

Cell& LineOfCells::back()
{
	return cells.back();
}

const Cell& LineOfCells::back() const
{
	return cells.back();
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
	return cells == other.cells;
}

bool LineOfCells::operator!=(const LineOfCells& other) const
{
	return cells != other.cells;
}

///
/// Returns a textual representation of LineOfCells.
/// This function is used by QCOMPARE() to output verbose
/// information in case of a test failure.
/// The caller of toString() must delete the returned data using delete[].
/// \param cells
/// \return pointer to c string alocated with new[]
///
char *toString(const LineOfCells& cells)
{
	std::string str = "[";
	for (int i = 0; i < cells.size(); i++)
	{
		str += CellSignUtils::toChar(cells.at(i).getSign());
	}
	str += "]";
	return qstrdup(str.c_str());
}
