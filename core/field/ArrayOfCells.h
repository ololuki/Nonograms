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
#ifndef ARRAYOFCELLS_H
#define ARRAYOFCELLS_H

#include "utils/NVector.h"
#include "Cell.h"


///
/// \brief ArrayOfCells stores Cells in 2-dimensional array.
/// Cells are accesible by operator(), use (x, y)
/// Cells are stored in vector of columns vector of Cells to make sure
/// that in operator[] first [] will be for x (column number)
/// and second [] will be for y (row number)
///
class ArrayOfCells
{
public:
	ArrayOfCells(int width, int height)
	{
		for (int i = 0; i < width; i++)
		{
			array.push_back(NVector<Cell>());
			for (int j = 0; j < height; j++)
			{
				array[i].push_back(Cell(AddressOfCell(i, j)));
			}
		}
	}
	Cell& operator()(int x, int y)
	{
		return array.at(x)[y];
	}
	const Cell& getPixelAt(int x, int y) const {
		return array.at(x).at(y);
	}
	int width() const;
	int height() const;
private:
	NVector<NVector<Cell>> array;
};

#endif // ARRAYOFCELLS_H
