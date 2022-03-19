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
#include "BlocksFromBordersSolver.h"

///
/// \brief Fill first and last blocks from first filled Cell
/// until Cell on position equal to block size.
/// Before:
/// 3 |-#---|
/// After:
/// 3 |-##--|
/// \param hints
/// \param cells
///
void BlocksFromBordersSolver::solve(const LineOfHints &hints, LineOfCells &cells) const
{
	if (hints.size() == 0)
	{
		return;
	}

	bool canFill = false;
	// first block on line front:
	for (int i = 0; i < hints.front().getBlockSize(); i++)
	{
		if (i < 0 || i >= cells.size())
		{
			return;
		}
		if (cells.at(i).isFilledBlack())
		{
			canFill = true;
		}
		if (canFill)
		{
			cells.at(i).makeFilledBlack();
		}
	}

	canFill = false;
	// last block on back of the line:
	for (int i = cells.size() - 1;
	     i >= static_cast<int>(cells.size() - hints.back().getBlockSize());
	     i--)
	{
		if (i < 0 || i >= cells.size())
		{
			return;
		}
		if (cells.at(i).isFilledBlack())
		{
			canFill = true;
		}
		if (canFill)
		{
			cells.at(i).makeFilledBlack();
		}
	}
	return;
}
