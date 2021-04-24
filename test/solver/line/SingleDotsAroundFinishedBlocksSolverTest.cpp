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
#include "SingleDotsAroundFinishedBlocksSolverTest.h"
#include <solver/line/SingleDotsAroundFinishedBlocksSolver.h>
#include <field/LineOfHints.h>
#include <field/LineOfCells.h>


void SingleDotsAroundFinishedBlocksSolverTest::first_block_solving_test_data()
{
	QTest::addColumn<LineOfHints>("d_lineOfHints");
	QTest::addColumn<LineOfCells>("d_startingLineOfCells");
	QTest::addColumn<LineOfCells>("d_expectedLineOfCells");

	QTest::newRow("Empty hints")
	        << LineOfHints()
	        << LineOfCells("---")
	        << LineOfCells("---");

	QTest::newRow("Block 1 from left start from 0")
	        << LineOfHints({Hint(1)})
	        << LineOfCells("#---")
	        << LineOfCells("#.--");

	QTest::newRow("Block 1 from left start from 1")
	        << LineOfHints({Hint(1)})
	        << LineOfCells("-#--")
	        << LineOfCells(".#.-");

	QTest::newRow("Block 3 from left start from 0")
	        << LineOfHints({Hint(3)})
	        << LineOfCells("###---")
	        << LineOfCells("###.--");

	QTest::newRow("Block 3 from left start from 1")
	        << LineOfHints({Hint(3)})
	        << LineOfCells("-###--")
	        << LineOfCells(".###.-");

	QTest::newRow("Block 3 from left start from some dots (more than length of block)")
	        << LineOfHints({Hint(3)})
	        << LineOfCells("......###---")
	        << LineOfCells("......###.--");

	QTest::newRow("Block 3 from left start from some dots (more than length of block) and one unresolved before block")
	        << LineOfHints({Hint(3)})
	        << LineOfCells(".....-###---")
	        << LineOfCells("......###.--");

	QTest::newRow("Block 3 from left start from 0, multiple blocks, others unfinished")
	        << LineOfHints({Hint(3), Hint(2), Hint(3)})
	        << LineOfCells("###------##-")
	        << LineOfCells("###.-----##-");

	QTest::newRow("Block 3 from left start from 1, multiple blocks, others unfinished")
	        << LineOfHints({Hint(3), Hint(2), Hint(3)})
	        << LineOfCells("-###-----##-")
	        << LineOfCells(".###.----##-");

	QTest::newRow("Unfinished block start from 0")
	        << LineOfHints({Hint(3)})
	        << LineOfCells("##---")
	        << LineOfCells("##---");

	QTest::newRow("Unfinished block start from 1")
	        << LineOfHints({Hint(3)})
	        << LineOfCells("-##--")
	        << LineOfCells("-##--");
}

void SingleDotsAroundFinishedBlocksSolverTest::first_block_solving_test()
{
	QFETCH(LineOfHints, d_lineOfHints);
	QFETCH(LineOfCells, d_startingLineOfCells);
	QFETCH(LineOfCells, d_expectedLineOfCells);

	AbstractLineSolver *solver = new SingleDotsAroundFinishedBlocksSolver();
	solver->solve(d_lineOfHints, d_startingLineOfCells);
	delete solver;

	QCOMPARE(d_startingLineOfCells, d_expectedLineOfCells);
}

void SingleDotsAroundFinishedBlocksSolverTest::last_block_solving_test_data()
{
	//TODO: implement
}

void SingleDotsAroundFinishedBlocksSolverTest::last_block_solving_test()
{
	//TODO: implement
}

void SingleDotsAroundFinishedBlocksSolverTest::biggest_block_solving_test_data()
{
	//TODO: implement
}

void SingleDotsAroundFinishedBlocksSolverTest::biggest_block_solving_test()
{
	//TODO: implement
}
