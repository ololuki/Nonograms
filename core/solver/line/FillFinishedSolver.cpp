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
#include "FillFinishedSolver.h"
#include <algorithm>


///
/// \brief Fill the rest of line if all filled black or all dots cells are drawn.
/// \param hints - line of hints
/// \param cells - current line of cells, unresolved cells will be changed
///
void FillFinishedSolver::solve(const LineOfHints& hints, LineOfCells& cells)
{
	int filledBlackInCells = std::count_if(cells.cbegin(), cells.cend(), [](const Cell& c){return c.isFilledBlack();});
	int filledBlackInHints = 0;
	for (const Hint& hint : hints)
	{
		filledBlackInHints += hint.getBlockSize();
	}

	// all filled black are finished, fill the rest with dots
	if (filledBlackInCells == filledBlackInHints)
	{
		for (Cell& cell : cells)
		{
			if (!cell.isFilledBlack())
			{
				cell.makeDot();
			}
		}
		return;
	}

	int dotsInCells = std::count_if(cells.cbegin(), cells.cend(), [](const Cell& c){return c.isDot();});
	int dotsInHints = cells.size() - filledBlackInHints;

	// all dots are finished, fill the rest with filled black
	if (dotsInCells == dotsInHints)
	{
		for (Cell& cell : cells)
		{
			if (!cell.isDot())
			{
				cell.makeFilledBlack();
			}
		}
	}
}
