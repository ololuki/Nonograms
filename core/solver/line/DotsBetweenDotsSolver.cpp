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
#include "DotsBetweenDotsSolver.h"
#include <algorithm>
#include <iterator>


///
/// \brief Draw dots in blocks of empty cells limited with dots on both ends
/// if that blocks are smaller than hint value.
/// \param hints - line of hints
/// \param cells - current line of cells, unresolved cells will be changed
///
void DotsBetweenDotsSolver::solve(const LineOfHints& hints, LineOfCells& cells) const
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
/// \brief Solve for first Hint, start from front.
/// \param hints - line of hints
/// \param cells - current line of cells, unresolved cells will be changed
///
void DotsBetweenDotsSolver::solveFirst(const LineOfHints& hints, LineOfCells& cells) const
{
	solveFirstLast(cells.begin(), cells.end(), hints.front().getBlockSize());
}

///
/// \brief Solve for last Hint, start from back.
/// \param hints - line of hints
/// \param cells - current line of cells, unresolved cells will be changed
///
void DotsBetweenDotsSolver::solveLast(const LineOfHints& hints, LineOfCells& cells) const
{
	solveFirstLast(cells.rbegin(), cells.rend(), hints.back().getBlockSize());
}

///
/// \brief Multiple empty blocks can be solved
/// as long as this blocks are smaller than first (or last) hint
/// and does not contain filled black cell.
/// \tparam T - LineOfCells::iterator for first;
///             LineOfCells::reverse_iterator for last
/// \param begin - begin for first; rbegin for last
/// \param end   - end for first;   rend for last
/// \param firstLastBlockSize - Block size from first or last Hint
///
template<typename T>
void DotsBetweenDotsSolver::solveFirstLast(T begin, T end, int firstLastBlockSize) const
{
	// true if start of block of empty cells was found
	bool isEmptyBlockStarted = false;
	// iterator to first Cell in block of empty cells
	T start;

	for (auto it = begin; it != end; ++it)
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
				if (std::distance(start, it) < firstLastBlockSize)
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

void DotsBetweenDotsSolver::solveSmallest(const LineOfHints& hints, LineOfCells& cells) const
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

	for (auto it = cells.begin(); it != cells.end(); ++it)
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
