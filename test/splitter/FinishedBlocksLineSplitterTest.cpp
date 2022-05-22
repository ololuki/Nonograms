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


Q_DECLARE_METATYPE(std::list<SubLine>)


void FinishedBlocksLineSplitterTest::split_test_data()
{
	QTest::addColumn<LineOfHints>("d_lineOfHints");
	QTest::addColumn<LineOfCells>("d_lineOfCells");
	QTest::addColumn<std::list<SubLine>>("d_expectedList");

	QTest::newRow("first finished and few empty returns one shorter subline (with trimmed dots on both ends)")
	        << LineOfHints({Hint(3), Hint(1), Hint(4)})
	        << LineOfCells(".###.-..----##-")
	        << std::list<SubLine>{{LineOfHints({Hint(1), Hint(4)}), {"-..----##-"}, 5}};

	QTest::newRow("first finished and few empty returns one shorter subline (with trimmed dots on both ends)")
	        << LineOfHints({Hint(3), Hint(1), Hint(4)})
	        << LineOfCells(".###....-----##-...")
	        << std::list<SubLine>{{LineOfHints({Hint(1), Hint(4)}), {"-----##-"}, 8}};

	QTest::newRow("last finished and few empty returns one shorter subline (with trimmed dots on both ends)")
	        << LineOfHints({Hint(4), Hint(1), Hint(3)})
	        << LineOfCells("-##----.--..###")
	        << std::list<SubLine>{{LineOfHints({Hint(4), Hint(1)}), {"-##----.--"}, 0}};

	QTest::newRow("all finished returns empty list")
	        << LineOfHints({Hint(3), Hint(3)})
	        << LineOfCells(".###.....###")
	        << std::list<SubLine>{};

	QTest::newRow("none finished returns empty list")
	        << LineOfHints({Hint(3), Hint(1), Hint(3)})
	        << LineOfCells(".-##--..----##-")
	        << std::list<SubLine>{};
}

void FinishedBlocksLineSplitterTest::split_test()
{
	QFETCH(LineOfHints, d_lineOfHints);
	QFETCH(LineOfCells, d_lineOfCells);
	QFETCH(std::list<SubLine>, d_expectedList);

	FinishedBlocksLineSplitter splitter;
	auto splittedList = splitter.split(d_lineOfHints, d_lineOfCells);

	QCOMPARE(splittedList.size(), d_expectedList.size());
	auto itExpected = d_expectedList.cbegin();
	for (const SubLine& subLine : splittedList)
	{
		QCOMPARE(subLine.offset, itExpected->offset);
		QCOMPARE(subLine.lineOfHints, itExpected->lineOfHints);
		QCOMPARE(subLine.lineOfCells, itExpected->lineOfCells);
		++itExpected;
	}
}
