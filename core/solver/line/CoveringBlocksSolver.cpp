/**********************************************************************
 * Copyright (C) 2017-2018 Ololuki
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
#include "CoveringBlocksSolver.h"


///
/// \brief Draw cells which are covering when start drawing from
/// begining and from end with gap size = 1.
/// \param hints - line of hints
/// \param cells - current line of cells, only unresolved cells will be changed
///
void CoveringBlocksSolver::solve(const LineOfHints &hints, LineOfCells &cells)
{
	// size of all blocks with gaps = 1; it is minimum posible lineOfCells size
	int minAllBlocksSize = 0;
	for (int i = 0; i < hints.size(); i++)
	{
		minAllBlocksSize += hints[i].getBlockSize();
	}
	// add gaps only between blocks, not at the end
	minAllBlocksSize += hints.size() - 1;
	
	// space left after blocks compression
	int gap = cells.size() - minAllBlocksSize;
	if (gap < 0) return; // error - too much blocks/cells - cannot be fit in line
	if (gap >= maxBlockSize(hints))
	{
		return; // nothing to be done - gap is too big
	}
	else
	{
		int currentPosition = -1; // last cell position (address) in current block
		// for each block
		for (int i = 0; i < hints.size(); i++)
		{
			currentPosition += hints[i].getBlockSize();
			if (hints[i].getBlockSize() > gap)
			{
				// for each covering cell in current block (backwards)
				for (int j = 0; j < hints[i].getBlockSize() - gap; j++)
				{
					if (currentPosition - j < 0 || currentPosition - j >= cells.size())
					{
						return; // error - array index out of bounds
					}
					cells[currentPosition - j].makeFilledBlack();
				}
			}
			currentPosition += 1; // one cell gap between blocks
		}
	}
}

int CoveringBlocksSolver::maxBlockSize(const LineOfHints &hints)
{
	int maxValue = 0;
	for (int i = 0; i < hints.size(); i++)
	{
		maxValue = hints[i].getBlockSize() > maxValue ? hints[i].getBlockSize() : maxValue;
	}
	return maxValue;
}
