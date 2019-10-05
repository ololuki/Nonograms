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
#include "ArrayOfCells.h"

bool ArrayOfCells::areSolvedCellsEqual(const ArrayOfCells& other)
{
	if (this->width() != other.width())
		return false;
	if (this->height() != other.height())
		return false;

	for (int x = 0; x < width(); x++)
	{
		for (int y = 0; y < height(); y ++)
		{
			const Cell& thisCell = array.at(x).at(y);
			const Cell& otherCell = other.getPixelAt(x, y);
			if(!thisCell.isEmpty() && !otherCell.isEmpty())
			{
				if(thisCell != otherCell)
				{
					return false;
				}
			}
		}
	}
	return true;
}

int ArrayOfCells::width() const
{
	return array.size();
}

int ArrayOfCells::height() const
{
	if (array.size() == 0)
	{
		return 0;
	}
	return array.at(0).size();
}
