/**********************************************************************
 * Copyright (C) 2021 - 2022 Ololuki
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


void SingleDotsAroundFinishedBlocksSolver::solve(const LineOfHints& hints, LineOfCells& cells) const
{
	if (hints.size() == 0)
	{
		return;
	}

	if (hints.front().getBlockSize() == 0)
	{
		return;
	}

	drawDotsOnFirstBlock(hints, cells);
	drawDotsOnLastBlock(hints, cells);
	drawDotsOnBiggestBlock(hints, cells);
}

///
/// \brief Draw dots around first finished block.
/// Before:
/// 2 3 |-##-----|
/// After:
/// 2 3 |.##.----|
/// \param hints - line of hints
/// \param cells - current line of cells, unresolved cells will be changed
///
void SingleDotsAroundFinishedBlocksSolver::drawDotsOnFirstBlock(const LineOfHints& hints, LineOfCells& cells) const
{
	if (hints.size() <= 1)
	{
		// solve with drawDotsOnBiggestBlock
		return;
	}

	int firstNonDotCell = 0;
	while (cells.at(firstNonDotCell).isDot())
	{
		++firstNonDotCell;
	}

	if (firstNonDotCell + hints.front().getBlockSize() >= cells.size())
	{
		return;
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
			// add dot after finished block (if there is any cell behind)
			if ((firstNonDotCell + hints.front().getBlockSize() + 1) < cells.size())
			{
				cells.at(firstNonDotCell + hints.front().getBlockSize() + 1).makeDot();
			}
		}
	}
}

///
/// \brief Draw dots around last finished block.
/// Before:
/// 2 3 |-#--###-|
/// After:
/// 2 3 |-#-.###.|
/// \param hints - line of hints
/// \param cells - current line of cells, unresolved cells will be changed
///
void SingleDotsAroundFinishedBlocksSolver::drawDotsOnLastBlock(const LineOfHints& hints, LineOfCells& cells) const
{
	if (hints.size() <= 1)
	{
		// solve with drawDotsOnBiggestBlock
		return;
	}

	int firstNonDotCell = cells.size() - 1;
	while (cells.at(firstNonDotCell).isDot())
	{
		--firstNonDotCell;
	}

	if (firstNonDotCell < hints.back().getBlockSize())
	{
		return;
	}

	bool isFullBlock = false; // if whole block is finished

	if (cells.at(firstNonDotCell).isFilledBlack())
	{
		// check if full block is filled black
		isFullBlock = true;
		for (int i = firstNonDotCell; i > firstNonDotCell - hints.back().getBlockSize(); i--)
		{
			if (!cells.at(i).isFilledBlack())
			{
				isFullBlock = false;
				break;
			}
		}
		if (isFullBlock)
		{
			// add dot before last finished block
			int dotPositionForLastBlock = firstNonDotCell - hints.back().getBlockSize();
			cells.at(dotPositionForLastBlock).makeDot();
		}
	}
	else
	{
		// first (backwards) non dot cell could be empty
		// so filled block could start from firstNonDotCell - 1
		// and if this block is finished then
		// dots before and after this block could be added
		isFullBlock = true;
		for (int i = firstNonDotCell - 1;
		     i > firstNonDotCell - hints.back().getBlockSize() - 1;
		     i--)
		{
			if (!cells.at(i).isFilledBlack())
			{
				isFullBlock = false;
				break;
			}
		}
		if (isFullBlock)
		{
			// add dot after finished block
			cells.at(firstNonDotCell).makeDot();
			// add dot before finished block (if there is any cell before)
			if (firstNonDotCell > (hints.back().getBlockSize()))
			{
				cells.at(firstNonDotCell - hints.back().getBlockSize() - 1).makeDot();
			}
		}
	}
}

///
/// \brief Draw dots around biggest finished blocks.
/// Multiple blocks can be solved.
/// \param hints - line of hints
/// \param cells - current line of cells, unresolved cells will be changed
///
void SingleDotsAroundFinishedBlocksSolver::drawDotsOnBiggestBlock(const LineOfHints& hints, LineOfCells& cells) const
{
	auto maxBlockSize = std::max_element(
	            hints.begin(),
	            hints.end(),
	            [](const Hint& a, const Hint& b) {return a.getBlockSize() < b.getBlockSize();}
	        )->getBlockSize();

	// number of cells continuously filled black
	int cellsContinuousFilled = 0;
	// last not filled black cell - init with invalid value
	LineOfCells::iterator lastNotFilled = cells.end();

	for (auto it = cells.begin(); it != cells.end(); ++it)
	{
		if (it->isFilledBlack())
		{
			++cellsContinuousFilled;
			if (cellsContinuousFilled == maxBlockSize)
			{
				// make dot before block (if block does not start from border)
				if (lastNotFilled != cells.end())
				{
					lastNotFilled->makeDot();
				}
				// make dot after block (if block does not end on border)
				if ((it + 1) != cells.end())
				{
					(it + 1)->makeDot();
				}
			}
		}
		else
		{
			cellsContinuousFilled = 0;
			lastNotFilled = it;
		}
	}
}
