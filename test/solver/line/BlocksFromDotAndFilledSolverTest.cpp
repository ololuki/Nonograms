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
#include "BlocksFromDotAndFilledSolverTest.h"
#include <solver/line/BlocksFromDotAndFilledSolver.h>
#include <field/LineOfHints.h>
#include <field/LineOfCells.h>


void BlocksFromDotAndFilledSolverTest::first_block_solving_test_data()
{
	QTest::addColumn<LineOfHints>("d_lineOfHints");
	QTest::addColumn<LineOfCells>("d_startingLineOfCells");
	QTest::addColumn<LineOfCells>("d_expectedLineOfCells");

	QTest::newRow("One place unfinished - start from border")
	        << LineOfHints({Hint(4)})
	        << LineOfCells("#-----------------")
	        << LineOfCells("####.-------------");

	QTest::newRow("One place unfinished - start from border, small, no dot on end")
	        << LineOfHints({Hint(4)})
	        << LineOfCells("#---")
	        << LineOfCells("####");

	QTest::newRow("One place unfinished - start from border, small, one dot on end")
	        << LineOfHints({Hint(4)})
	        << LineOfCells("#----")
	        << LineOfCells("####.");

	QTest::newRow("One place unfinished - start from border, small, dot and empty on end")
	        << LineOfHints({Hint(4)})
	        << LineOfCells("#-----")
	        << LineOfCells("####.-");

	QTest::newRow("One place unfinished - start with one dot")
	        << LineOfHints({Hint(4)})
	        << LineOfCells(".#-----------------")
	        << LineOfCells(".####.-------------");

	QTest::newRow("One place unfinished - start with some dots")
	        << LineOfHints({Hint(4)})
	        << LineOfCells("..#-----------------")
	        << LineOfCells("..####.-------------");

	QTest::newRow("One place unfinished - start with some dots, some additional free dots")
	        << LineOfHints({Hint(4)})
	        << LineOfCells("..#------.---.----..")
	        << LineOfCells("..####.--.---.----..");

	QTest::newRow("Two places unfinished - start from border")
	        << LineOfHints({Hint(4), Hint(2)})
	        << LineOfCells("#----#------------")
	        << LineOfCells("####.##.----------");

	QTest::newRow("Two places unfinished - start from border, second without dots around after one empty")
	        << LineOfHints({Hint(4), Hint(2)})
	        << LineOfCells("#-----#------------")
	        << LineOfCells("####.-#------------");

	QTest::newRow("Two places unfinished - start with some dots")
	        << LineOfHints({Hint(4), Hint(2)})
	        << LineOfCells("...#----#------------")
	        << LineOfCells("...####.##.----------");

	QTest::newRow("Two places unfinished - second without dots around")
	        << LineOfHints({Hint(4), Hint(2)})
	        << LineOfCells("...#-------#------------")
	        << LineOfCells("...####.---#------------");
}

void BlocksFromDotAndFilledSolverTest::first_block_solving_test()
{
	QFETCH(LineOfHints, d_lineOfHints);
	QFETCH(LineOfCells, d_startingLineOfCells);
	QFETCH(LineOfCells, d_expectedLineOfCells);

	AbstractLineSolver *solver = new BlocksFromDotAndFilledSolver();
	solver->solve(d_lineOfHints, d_startingLineOfCells);
	delete solver;

	QCOMPARE(d_startingLineOfCells, d_expectedLineOfCells);
}

void BlocksFromDotAndFilledSolverTest::last_block_solving_test_data()
{
	QTest::addColumn<LineOfHints>("d_lineOfHints");
	QTest::addColumn<LineOfCells>("d_startingLineOfCells");
	QTest::addColumn<LineOfCells>("d_expectedLineOfCells");

	QTest::newRow("One place unfinished - start from border")
	        << LineOfHints({Hint(4)})
	        << LineOfCells("---------#")
	        << LineOfCells("-----.####");

	QTest::newRow("One place unfinished - start from border, small, no dot on end")
	        << LineOfHints({Hint(4)})
	        << LineOfCells("---#")
	        << LineOfCells("####");

	QTest::newRow("One place unfinished - start from border, small, one dot on end")
	        << LineOfHints({Hint(4)})
	        << LineOfCells("----#")
	        << LineOfCells(".####");

	QTest::newRow("One place unfinished - start from border, small, dot and empty on end")
	        << LineOfHints({Hint(4)})
	        << LineOfCells("-----#")
	        << LineOfCells("-.####");

	QTest::newRow("One place unfinished - start with one dot")
	        << LineOfHints({Hint(4)})
	        << LineOfCells("---------------#.")
	        << LineOfCells("-----------.####.");

	QTest::newRow("One place unfinished - start with some dots")
	        << LineOfHints({Hint(4)})
	        << LineOfCells("---------------#..")
	        << LineOfCells("-----------.####..");

	QTest::newRow("One place unfinished - start with some dots, some additional free dots")
	        << LineOfHints({Hint(4)})
	        << LineOfCells("..----.--.-------#..")
	        << LineOfCells("..----.--.---.####..");

	QTest::newRow("Two places unfinished - start from border")
	        << LineOfHints({Hint(2), Hint(4)})
	        << LineOfCells("-----------#----#")
	        << LineOfCells("---------.##.####");

	QTest::newRow("Two places unfinished - start from border, second without dots around after one empty")
	        << LineOfHints({Hint(2), Hint(4)})
	        << LineOfCells("------------#-----#")
	        << LineOfCells("------------#-.####");

	QTest::newRow("Two places unfinished - start with some dots")
	        << LineOfHints({Hint(2), Hint(4)})
	        << LineOfCells("--------------#----#...")
	        << LineOfCells("------------.##.####...");

	QTest::newRow("Two places unfinished - second without dots around")
	        << LineOfHints({Hint(2), Hint(4)})
	        << LineOfCells("---------#-------#...")
	        << LineOfCells("---------#---.####...");
}

void BlocksFromDotAndFilledSolverTest::last_block_solving_test()
{
	QFETCH(LineOfHints, d_lineOfHints);
	QFETCH(LineOfCells, d_startingLineOfCells);
	QFETCH(LineOfCells, d_expectedLineOfCells);

	AbstractLineSolver *solver = new BlocksFromDotAndFilledSolver();
	solver->solve(d_lineOfHints, d_startingLineOfCells);
	delete solver;

	QCOMPARE(d_startingLineOfCells, d_expectedLineOfCells);
}

void BlocksFromDotAndFilledSolverTest::common_test_data()
{
	QTest::addColumn<LineOfHints>("d_lineOfHints");
	QTest::addColumn<LineOfCells>("d_startingLineOfCells");
	QTest::addColumn<LineOfCells>("d_expectedLineOfCells");

	QTest::newRow("Two places not from borders - only draw smallest possible number of cells")
	        << LineOfHints({Hint(3), Hint(4), Hint(2)})
	        << LineOfCells("------.#-------------#.-")
	        << LineOfCells("------.##-----------##.-");

	QTest::newRow("Two places unfinished - start from borders")
	        << LineOfHints({Hint(4), Hint(5)})
	        << LineOfCells("#---------------##")
	        << LineOfCells("####.-------.#####");

	QTest::newRow("Three places unfinished - start from borders, same block size")
	        << LineOfHints({Hint(3), Hint(3), Hint(3)})
	        << LineOfCells("#------.#-------##")
	        << LineOfCells("###.---.###---.###");

	QTest::newRow("Three places unfinished - start from borders, same block size")
	        << LineOfHints({Hint(3), Hint(3), Hint(3)})
	        << LineOfCells("#---------#.----##")
	        << LineOfCells("###.----###.--.###");
}

void BlocksFromDotAndFilledSolverTest::common_test()
{
	QFETCH(LineOfHints, d_lineOfHints);
	QFETCH(LineOfCells, d_startingLineOfCells);
	QFETCH(LineOfCells, d_expectedLineOfCells);

	AbstractLineSolver *solver = new BlocksFromDotAndFilledSolver();
	solver->solve(d_lineOfHints, d_startingLineOfCells);
	delete solver;

	QCOMPARE(d_startingLineOfCells, d_expectedLineOfCells);
}
