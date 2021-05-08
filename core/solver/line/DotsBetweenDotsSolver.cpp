/**********************************************************************
 * Copyright (C) 2021 Ololuki
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
#include "DotsBetweenDotsSolver.h"
#include <algorithm>
#include <iterator>


///
/// \brief Draw dots in blocks of empty cells limited with dots on both ends
/// if that blocks are smaller than hint value.
/// \param hints - line of hints
/// \param cells - current line of cells, unresolved cells will be changed
///
void DotsBetweenDotsSolver::solve(const LineOfHints& hints, LineOfCells& cells)
{
	if (hints.size() == 0)
	{
		return;
	}

	solveFirst(hints, cells);
	solveLast(hints, cells);
	solveSmallest(hints, cells);
}

///
/// \brief Multiple empty blocks can be solved
/// as long as this blocks are smaller than first hint
/// and does not contain filled black cell.
/// \param hints - line of hints
/// \param cells - current line of cells, unresolved cells will be changed
///
void DotsBetweenDotsSolver::solveFirst(const LineOfHints& hints, LineOfCells& cells)
{
	// true if start of block of empty cells was found
	bool isEmptyBlockStarted = false;
	// iterator to first element in block of empty cells
	NVector<Cell>::iterator start;

	for (auto it = cells.begin(); it != cells.end(); it++)
	{
		if (it->isFilledBlack())
		{
			return;
		}

		if (!isEmptyBlockStarted)
		{
			if (it->isEmpty())
			{
				start = it;
				isEmptyBlockStarted = true;
			}
		}
		else
		{
			if (it->isDot())
			{
				if (std::distance(start, it) < hints.front().getBlockSize())
				{
					std::for_each(start, it, [](Cell& c){c.makeDot();});
				}
				else
				{
					return;
				}
				isEmptyBlockStarted = false;
			}
		}
	}
}

void DotsBetweenDotsSolver::solveLast(const LineOfHints& hints, LineOfCells& cells)
{
	// TODO: implement
}

void DotsBetweenDotsSolver::solveSmallest(const LineOfHints& hints, LineOfCells& cells)
{
	auto minBlockSize = std::min_element(
	            hints.begin(),
	            hints.end(),
	            [](const Hint& a, const Hint& b) {return a.getBlockSize() < b.getBlockSize();}
	        )->getBlockSize();

	// true if start of block of empty (or filled black) cells was found
	bool isNonDotBlockStarted = false;
	// iterator to first element in block of empty (or filled black) cells
	NVector<Cell>::iterator start;
	// true if current block of non dot cells has filled black cell(s)
	bool blockHasFilledCells = false;

	for (auto it = cells.begin(); it != cells.end(); it++)
	{
		if (it->isFilledBlack())
		{
			blockHasFilledCells = true;
		}

		if (!isNonDotBlockStarted)
		{
			if (!it->isDot())
			{
				start = it;
				isNonDotBlockStarted = true;
			}
		}
		else
		{
			if (it->isDot())
			{
				if (!blockHasFilledCells)
				{
					if (std::distance(start, it) < minBlockSize)
					{
						std::for_each(start, it, [](Cell& c){c.makeDot();});
					}
				}
				isNonDotBlockStarted = false;
				blockHasFilledCells = false;
			}
		}
	}
}
