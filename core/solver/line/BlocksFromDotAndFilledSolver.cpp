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
#include "BlocksFromDotAndFilledSolver.h"
#include <algorithm>


void BlocksFromDotAndFilledSolver::solve(const LineOfHints& hints, LineOfCells& cells)
{
	solveFirst(hints, cells);
	solveLast(hints, cells);
	solveSmallest(hints, cells);
}

void BlocksFromDotAndFilledSolver::solveFirst(const LineOfHints& hints, LineOfCells& cells)
{
	solveFirstLast(hints.cbegin(), hints.cend(), cells.begin(), cells.end());
}

void BlocksFromDotAndFilledSolver::solveLast(const LineOfHints& hints, LineOfCells& cells)
{
	solveFirstLast(hints.crbegin(), hints.crend(), cells.rbegin(), cells.rend());
}

///
/// \brief Solve cells from dot followed by filled.
/// Start from first block (iterators) or from last (reverse_iterators).
/// Multiple blocks can be solved as long as it is possible.
///
/// \tparam TH - LineOfHints::const_iterator for forward;
///              LineOfHints::const_reverse_iterator for backward
/// \tparam TC - LineOfCells::iterator for forward;
///              LineOfCells::reverse_iterator for backward
/// \param hintsBegin - cbegin or crbegin
/// \param hintsEnd   - cend or crend
/// \param cellsBegin - begin or rbegin
/// \param cellsEnd   - end or rend
///
template<typename TH, typename TC>
void BlocksFromDotAndFilledSolver::solveFirstLast(TH hintsBegin, TH hintsEnd, TC cellsBegin, TC cellsEnd)
{
	auto hint = hintsBegin;
	// previous cell is dot - assume true if start from border
	bool isPreviousDot = true;
	for (auto it = cellsBegin; it != cellsEnd; ++it)
	{
		if (it->isEmpty())
		{
			return;
		}
		if (isPreviousDot)
		{
			if (it->isFilledBlack())
			{
				std::for_each(it,
				              it + hint->getBlockSize(),
				              [](Cell& c){c.makeFilledBlack();});
				if (hint->getBlockSize() < (cellsEnd - it))
				{
					(it + hint->getBlockSize())->makeDot();
				}
				if (++hint == hintsEnd)
				{
					return;
				}
			}
		}
		isPreviousDot = it->isDot();
	}
}

void BlocksFromDotAndFilledSolver::solveSmallest(const LineOfHints& hints, LineOfCells& cells)
{
	auto minBlockSize = std::min_element(
	            hints.begin(),
	            hints.end(),
	            [](const Hint& a, const Hint& b) {return a.getBlockSize() < b.getBlockSize();}
	        )->getBlockSize();

	fillSmallest(cells.begin(), cells.end(), minBlockSize);
	fillSmallest(cells.rbegin(), cells.rend(), minBlockSize);
}

///
/// \brief Fill smallestBlockSize cells from dot followed by filled.
/// \tparam T - LineOfCells::iterator for forward;
///             LineOfCells::reverse_iterator for backward
/// \param begin - begin or rbegin
/// \param end   - end or rend
/// \param smallestBlockSize - size of smallest block given in hints
///
template<typename T>
void BlocksFromDotAndFilledSolver::fillSmallest(T begin, T end, int smallestBlockSize)
{
	// previous cell is dot - assume true if start from border
	bool isPreviousDot = true;
	for (auto it = begin; it != end; ++it)
	{
		if (isPreviousDot)
		{
			if (it->isFilledBlack())
			{
				std::for_each(it,
				              it + smallestBlockSize,
				              [](Cell& c){c.makeFilledBlack();});
			}
		}
		isPreviousDot = it->isDot();
	}
}
