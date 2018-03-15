/**********************************************************************
 * Copyright (C) 2017-2018 Ololuki
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
#include "CoveringBlocksSolverTest.h"
#include <solver/line/AbstractLineSolver.h>
#include <solver/line/CoveringBlocksSolver.h>
#include <field/LineOfHints.h>
#include <field/LineOfCells.h>


void CoveringBlocksSolverTest::coveringBlocksSolver_is_type_of_abstractLineSolver()
{
	AbstractLineSolver *solver = new CoveringBlocksSolver();
	QVERIFY(solver);
	delete solver;
}

void CoveringBlocksSolverTest::solving_test_data()
{
	QTest::addColumn<LineOfHints>("d_lineOfHints");
	QTest::addColumn<LineOfCells>("d_startingLineOfCells");
	QTest::addColumn<LineOfCells>("d_expectedLineOfCells");
	
	QTest::newRow("Block 3 on line 3") << LineOfHints({Hint(3)}) << LineOfCells("---") << LineOfCells("###");
	QTest::newRow("Block 6 on line 7") << LineOfHints({Hint(6)}) << LineOfCells("-------") << LineOfCells("-#####-");
	QTest::newRow("Block 6 on line 9") << LineOfHints({Hint(6)}) << LineOfCells("---------") << LineOfCells("---###---");
	QTest::newRow("Block 6 on line 10") << LineOfHints({Hint(6)}) << LineOfCells("----------") << LineOfCells("----##----");
	QTest::newRow("Block 3 and 3 on line 8") << LineOfHints({Hint(3), Hint(3)}) << LineOfCells("--------") << LineOfCells("-##--##-");
	QTest::newRow("Block 4 on line 7 starting filled") << LineOfHints({Hint(4)}) << LineOfCells("-##----") << LineOfCells("-###---");
}

void CoveringBlocksSolverTest::solving_test()
{
	QFETCH(LineOfHints, d_lineOfHints);
	QFETCH(LineOfCells, d_startingLineOfCells);
	QFETCH(LineOfCells, d_expectedLineOfCells);
	
	AbstractLineSolver *solver = new CoveringBlocksSolver();
	solver->solve(d_lineOfHints, d_startingLineOfCells);
	delete solver;
	
	QVERIFY(areLineOfCellsEqualByCellSign(d_startingLineOfCells, d_expectedLineOfCells));
}

// TODO: move to LineOfCells
bool CoveringBlocksSolverTest::areLineOfCellsEqualByCellSign(LineOfCells &a, LineOfCells &b)
{
	if (a.size() != b.size())
		return false;
	for (int i = 0; i < a.size(); i++)
	{
		if (a.at(i).isFilledBlack() != b.at(i).isFilledBlack())
			return false;
		if (a.at(i).isDot() != b.at(i).isDot())
			return false;
	}
	return true;
}
