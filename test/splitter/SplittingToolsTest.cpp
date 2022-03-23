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
#include "SplittingToolsTest.h"
#include "splitter/SplittingTools.h"

Q_DECLARE_METATYPE(std::list<FinishedBlock>)


void SplittingToolsTest::find_finished_test_data()
{
	QTest::addColumn<LineOfCells>("d_lineOfCells");
	QTest::addColumn<std::list<FinishedBlock>>("d_expectedList");

	QTest::newRow("offset 0")
	        << LineOfCells("###.--")
	        << std::list<FinishedBlock>{{{3}, 0, true, false}};
	QTest::newRow("offset 1")
	        << LineOfCells(".###.--")
	        << std::list<FinishedBlock>{{{3}, 1, true, false}};
	QTest::newRow("offset 2")
	        << LineOfCells("..###.--")
	        << std::list<FinishedBlock>{{{3}, 2, true, false}};
	QTest::newRow("unfinished, offset 3")
	        << LineOfCells("--.###.--")
	        << std::list<FinishedBlock>{{{3}, 3, false, false}};

	QTest::newRow("all filled")
	        << LineOfCells("###")
	        << std::list<FinishedBlock>{{{3}, 0, true, true}};
	QTest::newRow("3+2 finished")
	        << LineOfCells("###.##")
	        << std::list<FinishedBlock>{{{3}, 0, true, true},
	                                    {{2}, 4, true, true}};
}

void SplittingToolsTest::find_finished_test()
{
	QFETCH(LineOfCells, d_lineOfCells);
	QFETCH(std::list<FinishedBlock>, d_expectedList);

	auto finishedList = SplittingTools::findFinished(d_lineOfCells);

	QCOMPARE(finishedList.size(), d_expectedList.size());
	auto itExpected = d_expectedList.cbegin();
	for (const FinishedBlock& finishedBlock : finishedList)
	{
		QCOMPARE(finishedBlock.hint, itExpected->hint);
		QCOMPARE(finishedBlock.offset, itExpected->offset);
		QCOMPARE(finishedBlock.allFinishedFromPrevBlock, itExpected->allFinishedFromPrevBlock);
		QCOMPARE(finishedBlock.allFinishedToNextBlock, itExpected->allFinishedToNextBlock);
		++itExpected;
	}
}
