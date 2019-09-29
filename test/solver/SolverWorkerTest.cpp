/**********************************************************************
 * Copyright (C) 2017-2019 Ololuki
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
#include "SolverWorkerTest.h"
#include <solver/SolverWorker.h>
#include <solver/field/DeductiveFieldSolver.h>


/// Worker with set FieldSolver should emit start and stop solving
void SolverWorkerTest::emitIsSolvedChangedTwiceAfterStartWorkerWithSolver()
{
	SolverWorker worker;
	WholeField wholeField = WholeField(1,1);
	QSignalSpy spy(&worker, &SolverWorker::isSolvingChanged);
	
	worker.setFieldSolver(std::make_shared<DeductiveFieldSolver>());
	worker.solve(wholeField);
	
	const int numberOfSignals = 2;
	spy.wait();
	QCOMPARE(spy.count(), numberOfSignals);
	QCOMPARE(qvariant_cast<bool>(spy.at(0).at(0)), true);
	QCOMPARE(qvariant_cast<bool>(spy.at(1).at(0)), false);
}

/// Empty worker mean that there are not line solvers or field solvers.
void SolverWorkerTest::notEmitIsSolvingChangedAfterStartEmptyWorker()
{
	SolverWorker worker;
	WholeField wholeField = WholeField(1,1);
	QSignalSpy spyIsSolving(&worker, &SolverWorker::isSolvingChanged);

	worker.solve(wholeField);

	spyIsSolving.wait(0); // timeout 0, because isSolvingChange is emited in solve method
	const int numberOfIsSolvingChanged = 0;
	QCOMPARE(spyIsSolving.count(), numberOfIsSolvingChanged);
}
