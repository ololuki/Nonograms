/**********************************************************************
 * Copyright (C) 2017 - 2019 Ololuki
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
#include "DeductiveFieldSolverTest.h"
#include <solver/field/DeductiveFieldSolver.h>

Q_DECLARE_METATYPE(CellsField)
Q_DECLARE_METATYPE(HintsField)

void DeductiveFieldSolverTest::initialStateShouldBeNotStarted()
{
	DeductiveFieldSolver solver;
	QCOMPARE(solver.getState(), DeductiveFieldSolver::State::notStarted);
}

/// After solve() state should be changed to solving or finished
void DeductiveFieldSolverTest::stateShouldBeDifferentThanNotStartedAfterSolve()
{
	DeductiveFieldSolver solver;
	solver.solveOneStep();
	QVERIFY(solver.getState() != DeductiveFieldSolver::State::notStarted);
}

void DeductiveFieldSolverTest::solving_test_data()
{
	QTest::addColumn<CellsField>("d_cellsField");
	QTest::addColumn<HintsField>("d_rowsHints");
	QTest::addColumn<HintsField>("d_columnsHints");

	QTest::newRow("Block 3 on line 3")
	        << CellsField{{"------"}, {"------"}, {"--###-"}}
	        << HintsField{Orientation::HORIZONTAL, {{{Hint(0)}}, {{Hint(0)}}, {{Hint(3)}}}}
	        << HintsField{Orientation::VERTICAL, {{{Hint(0)}}, {{Hint(0)}}, {{Hint(1)}}, {{Hint(1)}}, {{Hint(1)}}, {{Hint(0)}}}};
}

/// Check if solver works.
/// Currently only resolved cells are compared, because solver is unfinished,
/// but in the future we can check if whole field was resolved.
/// Currently test checks if solver does not resolve cells to wrong values.
void DeductiveFieldSolverTest::solving_test()
{
	QFETCH(CellsField, d_cellsField);
	QFETCH(HintsField, d_rowsHints);
	QFETCH(HintsField, d_columnsHints);
	DeductiveFieldSolver solver;
	solver.setWholeField(WholeField(d_cellsField, d_columnsHints, d_rowsHints));
	while(solver.getState() != DeductiveFieldSolver::finished)
	{
		solver.solveOneStep();
	}

	QVERIFY(solver.getWholeField().cells().areSolvedCellsEqual(d_cellsField));

	// TODO: check if field is resolved
}
