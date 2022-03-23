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
#include "FinishedBlocksLineSplitter.h"
#include "FinishedBlock.h"
#include "SplittingTools.h"
#include <set>
#include <map>


std::list<SubLine> FinishedBlocksLineSplitter::split(const LineOfHints& lineOfHints, const LineOfCells& lineOfCells) const
{
	std::list<SubLine> list;

	auto finishedList = SplittingTools::findFinished(lineOfCells);
	if (finishedList.empty() || finishedList.size() == lineOfHints.size())
	{
		return list;
	}

	std::multiset<Hint> sortedHints;
	for (const auto& hint : lineOfHints)
	{
		sortedHints.insert(hint);
	}

	std::multimap<Hint, FinishedBlock> finishedMap;
	for (const auto& finishedBlock : finishedList)
	{
		finishedMap.emplace(finishedBlock.hint,
		                    finishedBlock);
	}

	// starting points for next SubLine
	auto itPreviousHint = lineOfHints.cbegin();
	auto itPreviousCell = lineOfCells.cbegin();
	// current finished block
	auto itFinished = finishedList.cbegin();

	for (auto itHint = lineOfHints.cbegin(); itHint != lineOfHints.cend(); ++itHint)
	{
		// TODO: || all finished from start
		if (sortedHints.count(*itHint) == finishedMap.count(*itHint))
		{
			// create SubLine if there was any unfinished Cell
			if (!itFinished->allFinishedFromPrevBlock)
			{
				// make split
				SubLine subline;
				subline.offset = itPreviousCell - lineOfCells.cbegin();
				subline.lineOfHints = LineOfHints(NVector<Hint>(itPreviousHint, itHint));
				// TODO: trim dots on the ends
				subline.lineOfCells = LineOfCells(NVector<Cell>(itPreviousCell, lineOfCells.cbegin() + itFinished->offset - 1));
				list.push_back(subline);
			}
			// We can advance previous iterator, because we saved SubLine
			// or all Cells was finished so we do not need Subline here.
			// cut out finished Hint - next SubLine should not contain finished blocks
			itPreviousHint = itHint + 1;
			// dot after finished block
			itPreviousCell = lineOfCells.cbegin() + itFinished->offset + itHint->getBlockSize();

			++itFinished;
		}
	}
	// last SubLine until end
	if (!finishedList.back().allFinishedToNextBlock)
	{
		// make until the end
		SubLine subline;
		subline.offset = itPreviousCell - lineOfCells.cbegin();
		subline.lineOfHints = LineOfHints(NVector<Hint>(itPreviousHint, lineOfHints.cend()));
		// TODO: trim dots on the ends
		subline.lineOfCells = LineOfCells(NVector<Cell>(itPreviousCell, lineOfCells.cend()));
		list.push_back(subline);
	}

	return list;
}
