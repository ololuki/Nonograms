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
#include "SolverWorker.h"
#include "field/AbstractFieldSolver.h"
#include <QDebug>


SolverWorker::SolverWorker()
{
	connect(this,
		&SolverWorker::queueNextJob,
		this,
		&SolverWorker::doJob,
		Qt::QueuedConnection
	);
}

void SolverWorker::setFieldSolver(std::shared_ptr<AbstractFieldSolver> solver)
{
	this->solver = solver;
	this->solver->registerObserver(this);
}

void SolverWorker::solve(WholeField wholeField)
{
	if(solver)
	{
		solver->setWholeField(wholeField);
		solving = true;
		emit isSolvingChanged(solving);
		emit queueNextJob();
	}
	else
	{
		qCritical() << "solver not set!";
	}
}

void SolverWorker::stop()
{
	solving = false;
	emit isSolvingChanged(solving);
}

void SolverWorker::onCellChanged(Cell cell)
{
	emit cellChanged(cell);
}

void SolverWorker::doJob()
{
	if (!solving)
		return;

	solver->solveOneStep();

	if(solver->getState() == AbstractFieldSolver::State::finished)
	{
		solving = false;
		emit isSolvingChanged(solving);
	}
	else
	{
		emit queueNextJob();
	}
}
