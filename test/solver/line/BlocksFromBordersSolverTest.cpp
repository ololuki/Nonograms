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
#include "BlocksFromBordersSolverTest.h"
#include <solver/line/BlocksFromBordersSolver.h>
#include <field/LineOfHints.h>
#include <field/LineOfCells.h>


void BlocksFromBordersSolverTest::solving_test_data()
{
	QTest::addColumn<LineOfHints>("d_lineOfHints");
	QTest::addColumn<LineOfCells>("d_startingLineOfCells");
	QTest::addColumn<LineOfCells>("d_expectedLineOfCells");

	QTest::newRow("Empty hints")
	        << LineOfHints()
	        << LineOfCells("---")
	        << LineOfCells("---");

	QTest::newRow("Empty hints with dot")
	        << LineOfHints()
	        << LineOfCells("-.-")
	        << LineOfCells("-.-");

	QTest::newRow("Block 3 from left full")
	        << LineOfHints({Hint(3)})
	        << LineOfCells("#--")
	        << LineOfCells("###");

	QTest::newRow("Block 3 from right full")
	        << LineOfHints({Hint(3)})
	        << LineOfCells("--#")
	        << LineOfCells("###");

	QTest::newRow("Block 3 on line 7 from left")
	        << LineOfHints({Hint(3)})
	        << LineOfCells("#------")
	        << LineOfCells("###----");

	QTest::newRow("Block 4 on line 9 from left, start on second")
	        << LineOfHints({Hint(4)})
	        << LineOfCells("-#-------")
	        << LineOfCells("-###-----");

	QTest::newRow("Block 3 and 3 on line 8")
	        << LineOfHints({Hint(3), Hint(3)})
	        << LineOfCells("#-----#-")
	        << LineOfCells("###--##-");

	QTest::newRow("Block 3 and 3 on line 10")
	        << LineOfHints({Hint(3), Hint(3)})
	        << LineOfCells("--#------#")
	        << LineOfCells("--#----###");

	QTest::newRow("Block 3, 3 and 3 on line 15")
	        << LineOfHints({Hint(3), Hint(3)})
	        << LineOfCells("#--------#---#-")
	        << LineOfCells("###------#--##-");

	QTest::newRow("Block 3, 3 and 3 on line 15")
	        << LineOfHints({Hint(3), Hint(3)})
	        << LineOfCells("--#------#---#-")
	        << LineOfCells("--#------#--##-");

	QTest::newRow("Block 3, 3 and 3 on line 15, nothing to do")
	        << LineOfHints({Hint(3), Hint(3)})
	        << LineOfCells("--#----#---#---")
	        << LineOfCells("--#----#---#---");

	QTest::newRow("Block 3, 3 and 3 on line 15, nothing to do - fully resolved")
	        << LineOfHints({Hint(3), Hint(3)})
	        << LineOfCells("###----###-###-")
	        << LineOfCells("###----###-###-");
}

void BlocksFromBordersSolverTest::solving_test()
{
	QFETCH(LineOfHints, d_lineOfHints);
	QFETCH(LineOfCells, d_startingLineOfCells);
	QFETCH(LineOfCells, d_expectedLineOfCells);

	AbstractLineSolver *solver = new BlocksFromBordersSolver();
	solver->solve(d_lineOfHints, d_startingLineOfCells);
	delete solver;

	QCOMPARE(d_startingLineOfCells, d_expectedLineOfCells);
}
