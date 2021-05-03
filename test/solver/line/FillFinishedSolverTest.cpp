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
#include "FillFinishedSolverTest.h"
#include <solver/line/FillFinishedSolver.h>
#include <field/LineOfHints.h>
#include <field/LineOfCells.h>


void FillFinishedSolverTest::test_data()
{
	QTest::addColumn<LineOfHints>("d_lineOfHints");
	QTest::addColumn<LineOfCells>("d_startingLineOfCells");
	QTest::addColumn<LineOfCells>("d_expectedLineOfCells");

	QTest::newRow("Empty")
	        << LineOfHints()
	        << LineOfCells("----")
	        << LineOfCells("....");

	QTest::newRow("One block full size")
	        << LineOfHints({Hint(5)})
	        << LineOfCells("-----")
	        << LineOfCells("#####");

	QTest::newRow("Two blocks - only filled finished")
	        << LineOfHints({Hint(4), Hint(2)})
	        << LineOfCells("---####----##----")
	        << LineOfCells("...####....##....");

	QTest::newRow("Two blocks - only dots finished")
	        << LineOfHints({Hint(4), Hint(2)})
	        << LineOfCells("...----....--....")
	        << LineOfCells("...####....##....");

	QTest::newRow("Three blocks - filled finished and some dots")
	        << LineOfHints({Hint(4), Hint(2), Hint(5)})
	        << LineOfCells("-.-####....##---#####-")
	        << LineOfCells("...####....##...#####.");

	QTest::newRow("Three blocks - dots finished and some filled black")
	        << LineOfHints({Hint(6), Hint(2), Hint(4)})
	        << LineOfCells("...------....--....-##-")
	        << LineOfCells("...######....##....####");
}

void FillFinishedSolverTest::test()
{
	QFETCH(LineOfHints, d_lineOfHints);
	QFETCH(LineOfCells, d_startingLineOfCells);
	QFETCH(LineOfCells, d_expectedLineOfCells);

	AbstractLineSolver *solver = new FillFinishedSolver();
	solver->solve(d_lineOfHints, d_startingLineOfCells);
	delete solver;

	QCOMPARE(d_startingLineOfCells, d_expectedLineOfCells);
}
