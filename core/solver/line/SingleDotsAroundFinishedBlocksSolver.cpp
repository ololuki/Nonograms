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
#include "SingleDotsAroundFinishedBlocksSolver.h"


void SingleDotsAroundFinishedBlocksSolver::solve(const LineOfHints& hints, LineOfCells& cells)
{
	drawDotsOnFirstBlock(hints, cells);
	drawDotsOnLastBlock(hints, cells);
	drawDotsOnBiggestBlock(hints, cells);
}

void SingleDotsAroundFinishedBlocksSolver::drawDotsOnFirstBlock(const LineOfHints& hints, LineOfCells& cells)
{
	if (hints.size() == 0)
	{
		return;
	}

	if (hints.front().getBlockSize() == 0)
	{
		return;
	}

	int firstNonDotCell = 0;
	while (cells.at(firstNonDotCell).isDot())
	{
		++firstNonDotCell;
	}

	bool isFullBlock = false; // if whole block is finished

	if (cells.at(firstNonDotCell).isFilledBlack())
	{
		// check if full block is filled black
		isFullBlock = true;
		for (int i = 0; i < hints.front().getBlockSize(); i++)
		{
			if (!cells.at(firstNonDotCell + i).isFilledBlack())
			{
				isFullBlock = false;
				break;
			}
		}
		if (isFullBlock)
		{
			// add dot after finished block
			cells.at(firstNonDotCell + hints.front().getBlockSize()).makeDot();
		}
	}
	else
	{
		// first non dot cell could be empty
		// so filled block could start from firstNonDotCell + 1
		// and if this block is finished then
		// dots before and after this block could be added
		isFullBlock = true;
		for (int i = 1; i < hints.front().getBlockSize() + 1; i++)
		{
			if (!cells.at(firstNonDotCell + i).isFilledBlack())
			{
				isFullBlock = false;
				break;
			}
		}
		if (isFullBlock)
		{
			// add dot before finished block
			cells.at(firstNonDotCell).makeDot();
			// add dot after finished block
			cells.at(firstNonDotCell + hints.front().getBlockSize() + 1).makeDot();
		}
	}
}

void SingleDotsAroundFinishedBlocksSolver::drawDotsOnLastBlock(const LineOfHints& hints, LineOfCells& cells)
{
	//	TODO: implement
}

void SingleDotsAroundFinishedBlocksSolver::drawDotsOnBiggestBlock(const LineOfHints& hints, LineOfCells& cells)
{
	//	TODO: implement
}
