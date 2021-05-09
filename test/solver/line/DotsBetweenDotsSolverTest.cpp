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
#include "DotsBetweenDotsSolverTest.h"
#include <solver/line/DotsBetweenDotsSolver.h>
#include <field/LineOfHints.h>
#include <field/LineOfCells.h>


void DotsBetweenDotsSolverTest::first_block_solving_test_data()
{
	QTest::addColumn<LineOfHints>("d_lineOfHints");
	QTest::addColumn<LineOfCells>("d_startingLineOfCells");
	QTest::addColumn<LineOfCells>("d_expectedLineOfCells");

	QTest::newRow("One place smaller than hint - begin from border")
	        << LineOfHints({Hint(3), Hint(5)})
	        << LineOfCells("--..------------------")
	        << LineOfCells("....------------------");

	QTest::newRow("One place smaller than first hint - begin from border")
	        << LineOfHints({Hint(2), Hint(1)})
	        << LineOfCells("-..------------------")
	        << LineOfCells("...------------------");

	QTest::newRow("One place smaller than hint")
	        << LineOfHints({Hint(3), Hint(5)})
	        << LineOfCells(".--..------------------")
	        << LineOfCells(".....------------------");

	QTest::newRow("One place smaller than first hint")
	        << LineOfHints({Hint(2), Hint(1)})
	        << LineOfCells(".-..------------------")
	        << LineOfCells("....------------------");

	QTest::newRow("Two places smaller than hint - begin from border")
	        << LineOfHints({Hint(3), Hint(5)})
	        << LineOfCells("--..-..-----------------")
	        << LineOfCells(".......-----------------");

	QTest::newRow("Two places smaller than first hint")
	        << LineOfHints({Hint(3), Hint(1)})
	        << LineOfCells(".--..-..-----------------")
	        << LineOfCells("........-----------------");

	QTest::newRow("Two places smaller than first hint - start with multiple dots")
	        << LineOfHints({Hint(3), Hint(1)})
	        << LineOfCells(".....--..-..-----------------")
	        << LineOfCells("............-----------------");

	QTest::newRow("One place equal to hint - begin from border - do nothing")
	        << LineOfHints({Hint(3), Hint(5)})
	        << LineOfCells("---..------------------")
	        << LineOfCells("---..------------------");

	QTest::newRow("One place equal to hint - do nothing")
	        << LineOfHints({Hint(3), Hint(5)})
	        << LineOfCells(".---..------------------")
	        << LineOfCells(".---..------------------");

	QTest::newRow("Two places equal to hint - do nothing")
	        << LineOfHints({Hint(3), Hint(5)})
	        << LineOfCells(".---..---..-------------")
	        << LineOfCells(".---..---..-------------");

	QTest::newRow("One place greater than hint - do nothing")
	        << LineOfHints({Hint(3), Hint(5)})
	        << LineOfCells(".----..------------------")
	        << LineOfCells(".----..------------------");

	QTest::newRow("Two places greater than hint - do nothing")
	        << LineOfHints({Hint(3), Hint(5)})
	        << LineOfCells(".----..------..----------")
	        << LineOfCells(".----..------..----------");

	QTest::newRow("Two places greater and smaller than first hint - do nothing")
	        << LineOfHints({Hint(4), Hint(2)})
	        << LineOfCells(".-----..---..----------")
	        << LineOfCells(".-----..---..----------");

	QTest::newRow("Two places smaller and greater than first hint - fill only smaller")
	        << LineOfHints({Hint(3), Hint(5)})
	        << LineOfCells(".--..-----..----------")
	        << LineOfCells(".....-----..----------");

	QTest::newRow("Two places, but first have filled cell - begin from border - do nothing")
	        << LineOfHints({Hint(3), Hint(5)})
	        << LineOfCells("#--..-----..----------")
	        << LineOfCells("#--..-----..----------");

	QTest::newRow("Two places, but first have filled cell - do nothing")
	        << LineOfHints({Hint(3), Hint(5)})
	        << LineOfCells(".#--..-----..----------")
	        << LineOfCells(".#--..-----..----------");
}

void DotsBetweenDotsSolverTest::first_block_solving_test()
{
	QFETCH(LineOfHints, d_lineOfHints);
	QFETCH(LineOfCells, d_startingLineOfCells);
	QFETCH(LineOfCells, d_expectedLineOfCells);

	AbstractLineSolver *solver = new DotsBetweenDotsSolver();
	solver->solve(d_lineOfHints, d_startingLineOfCells);
	delete solver;

	QCOMPARE(d_startingLineOfCells, d_expectedLineOfCells);
}

void DotsBetweenDotsSolverTest::last_block_solving_test_data()
{
	QTest::addColumn<LineOfHints>("d_lineOfHints");
	QTest::addColumn<LineOfCells>("d_startingLineOfCells");
	QTest::addColumn<LineOfCells>("d_expectedLineOfCells");

	QTest::newRow("One place smaller than last hint - start from border")
	        << LineOfHints({Hint(2), Hint(3)})
	        << LineOfCells(".---------.--")
	        << LineOfCells(".---------...");

	QTest::newRow("One place smaller than last hint - start from border")
	        << LineOfHints({Hint(2), Hint(3)})
	        << LineOfCells(".---------.-")
	        << LineOfCells(".---------..");

	QTest::newRow("One place smaller than last hint")
	        << LineOfHints({Hint(2), Hint(3)})
	        << LineOfCells(".---------.--.")
	        << LineOfCells(".---------....");

	QTest::newRow("One place smaller than last hint")
	        << LineOfHints({Hint(1), Hint(3)})
	        << LineOfCells(".---------.-.")
	        << LineOfCells(".---------...");
}

void DotsBetweenDotsSolverTest::last_block_solving_test()
{
	QFETCH(LineOfHints, d_lineOfHints);
	QFETCH(LineOfCells, d_startingLineOfCells);
	QFETCH(LineOfCells, d_expectedLineOfCells);

	AbstractLineSolver *solver = new DotsBetweenDotsSolver();
	solver->solve(d_lineOfHints, d_startingLineOfCells);
	delete solver;

	QCOMPARE(d_startingLineOfCells, d_expectedLineOfCells);
}

void DotsBetweenDotsSolverTest::smallest_block_solving_test_data()
{
	QTest::addColumn<LineOfHints>("d_lineOfHints");
	QTest::addColumn<LineOfCells>("d_startingLineOfCells");
	QTest::addColumn<LineOfCells>("d_expectedLineOfCells");

	QTest::newRow("Places greater, equal and smaller than hints")
	        << LineOfHints({Hint(3), Hint(5)})
	        << LineOfCells(".------...-----.----..---.--..----------")
	        << LineOfCells(".------...-----.----..---.....----------");

	QTest::newRow("4 places smaller and 2 greater than hint")
	        << LineOfHints({Hint(2), Hint(3)})
	        << LineOfCells(".-..-..-...-----.-.----")
	        << LineOfCells("...........-----...----");

	QTest::newRow("Hint size 1 - do nothing")
	        << LineOfHints({Hint(1), Hint(3)})
	        << LineOfCells(".-..-..-...-----.-.----")
	        << LineOfCells(".-..-..-...-----.-.----");

	QTest::newRow("Some resolved cells in places equal to hint should not be touched")
	        << LineOfHints({Hint(3), Hint(3), Hint(3), Hint(3)})
	        << LineOfCells(".--#.#--.-#-.-----.-.-.###")
	        << LineOfCells(".--#.#--.-#-.-----.....###");
}

void DotsBetweenDotsSolverTest::smallest_block_solving_test()
{
	QFETCH(LineOfHints, d_lineOfHints);
	QFETCH(LineOfCells, d_startingLineOfCells);
	QFETCH(LineOfCells, d_expectedLineOfCells);

	AbstractLineSolver *solver = new DotsBetweenDotsSolver();
	solver->solve(d_lineOfHints, d_startingLineOfCells);
	delete solver;

	QCOMPARE(d_startingLineOfCells, d_expectedLineOfCells);
}

void DotsBetweenDotsSolverTest::common_test_data()
{
	QTest::addColumn<LineOfHints>("d_lineOfHints");
	QTest::addColumn<LineOfCells>("d_startingLineOfCells");
	QTest::addColumn<LineOfCells>("d_expectedLineOfCells");

	QTest::newRow("No hints - do nothing")
	        << LineOfHints()
	        << LineOfCells("----....-----.----..---.--..----------")
	        << LineOfCells("----....-----.----..---.--..----------");

	QTest::newRow("First start from border smaller than first hint and some empty blocks in center")
	        << LineOfHints({Hint(5), Hint(3)})
	        << LineOfCells("----....-----.----..---.--..----------")
	        << LineOfCells("........-----.----..---.....----------");

	QTest::newRow("Last start from border smaller than last hint and some empty blocks in center")
	        << LineOfHints({Hint(3), Hint(5)})
	        << LineOfCells("------.----..---.--..------.---")
	        << LineOfCells("------.----..---.....------....");
}

void DotsBetweenDotsSolverTest::common_test()
{
	QFETCH(LineOfHints, d_lineOfHints);
	QFETCH(LineOfCells, d_startingLineOfCells);
	QFETCH(LineOfCells, d_expectedLineOfCells);

	AbstractLineSolver *solver = new DotsBetweenDotsSolver();
	solver->solve(d_lineOfHints, d_startingLineOfCells);
	delete solver;

	QCOMPARE(d_startingLineOfCells, d_expectedLineOfCells);
}
