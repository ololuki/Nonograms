/**********************************************************************
 * Copyright (C) 2022 Ololuki
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
#include "SplittingTools.h"
#include "field/Hint.h"


std::list<FinishedBlock> SplittingTools::findFinished(const LineOfCells& lineOfCells)
{
	std::list<FinishedBlock> list;
	int currentBlockCounter = 0; // number of Cells counted in current block
	bool isCurrentBlockContinuous = false;
	Cell previous(cellSign::SGN_DOT);
	bool allFinishedFromPrevBlock = true;

	for (int i = 0; i < lineOfCells.size(); i++)
	{
		if (lineOfCells.at(i).isDot())
		{
			if (previous.isFilledBlack())
			{
				// previous block was continuous
				if (isCurrentBlockContinuous)
				{
					if (!list.empty())
					{
						list.back().allFinishedToNextBlock = allFinishedFromPrevBlock;
					}
					list.push_back({Hint(currentBlockCounter, previous.getSign()),
					                i - currentBlockCounter,
					                allFinishedFromPrevBlock,
					                false}); // will be filled in the future
					allFinishedFromPrevBlock = true;
				}
			}
			currentBlockCounter = 0;
			isCurrentBlockContinuous = false;
		}
		else if (lineOfCells.at(i).isFilledBlack())
		{
			++currentBlockCounter;
			if (previous.isDot())
			{
				isCurrentBlockContinuous = true;
			}
		}
		else if (lineOfCells.at(i).isEmpty())
		{
			isCurrentBlockContinuous = false;
			allFinishedFromPrevBlock = false;
		}
		// prepare for next iteration
		previous = lineOfCells.at(i);
	}

	// Last block ends on wall
	if (previous.isFilledBlack())
	{
		// previous block was continuous
		if (isCurrentBlockContinuous)
		{
			if (!list.empty())
			{
				list.back().allFinishedToNextBlock = allFinishedFromPrevBlock;
			}
			list.push_back({Hint(currentBlockCounter, previous.getSign()),
			                lineOfCells.size() - currentBlockCounter,
			                allFinishedFromPrevBlock,
			                true}); // last block ends on wall - so all next 0 Cells are finished
		}
	}
	else if (!list.empty())
	{
		// if all Cells after last block are dots
		for (auto it = lineOfCells.crbegin(); it != lineOfCells.crend(); ++it)
		{
			if (it->isEmpty())
			{
				break;
			}
			else if (it->isFilledBlack())
			{
				list.back().allFinishedToNextBlock = true;
			}
		}
	}

	return list;
}
