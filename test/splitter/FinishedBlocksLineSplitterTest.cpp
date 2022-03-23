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
#include "FinishedBlocksLineSplitterTest.h"
#include "splitter/FinishedBlocksLineSplitter.h"


void FinishedBlocksLineSplitterTest::first_finished_and_few_empty_returns_one_shorter_subline()
{
	LineOfHints lineOfHints({Hint(3), Hint(1), Hint(4)});
	LineOfCells lineOfCells(".###.-..----##-");
	FinishedBlocksLineSplitter splitter;
	auto splittedList = splitter.split(lineOfHints, lineOfCells);

	QVERIFY(splittedList.size() == 1);
	QVERIFY(splittedList.front().offset == 4);
	QCOMPARE(splittedList.front().lineOfCells, LineOfCells(".-..----##-"));
	QCOMPARE(splittedList.front().lineOfHints, LineOfHints({Hint(1), Hint(4)}));
}

void FinishedBlocksLineSplitterTest::last_finished_and_few_empty_returns_one_shorter_subline()
{
	LineOfHints lineOfHints({Hint(4), Hint(1), Hint(3)});
	LineOfCells lineOfCells("-##----.--..###");
	FinishedBlocksLineSplitter splitter;
	auto splittedList = splitter.split(lineOfHints, lineOfCells);
	QVERIFY(splittedList.size() == 1);

	QVERIFY(splittedList.front().offset == 0);
	QCOMPARE(splittedList.front().lineOfCells, LineOfCells("-##----.--."));
	QCOMPARE(splittedList.front().lineOfHints, LineOfHints({Hint(4), Hint(1)}));
}

/// All finished so nothing to solve
void FinishedBlocksLineSplitterTest::all_finished_returns_empty_list()
{
	LineOfHints lineOfHints({Hint(3), Hint(3)});
	LineOfCells lineOfCells(".###.....###");
	FinishedBlocksLineSplitter splitter;
	auto splittedList = splitter.split(lineOfHints, lineOfCells);

	QVERIFY(splittedList.size() == 0);
}

/// None finished so no sublines
void FinishedBlocksLineSplitterTest::none_finished_returns_empty_list()
{
	LineOfHints lineOfHints({Hint(3), Hint(1), Hint(3)});
	LineOfCells lineOfCells(".-##--..----##-");
	FinishedBlocksLineSplitter splitter;
	auto splittedList = splitter.split(lineOfHints, lineOfCells);

	QVERIFY(splittedList.size() == 0);
}
