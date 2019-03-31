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
#ifndef SOLVERWORKER_H
#define SOLVERWORKER_H

#include "../field/WholeFieldModel.h"
#include "line/AbstractLineSolver.h"
#include <QObject>
#include <QVector>
#include <memory>


class SolverWorker : public QObject
{
	Q_OBJECT
public:
	SolverWorker();
	
	void solve(WholeField wholeField);
	void stop();
	void addLineSolver(std::shared_ptr<AbstractLineSolver> solver);
	
signals:
	void queueNextJob();
	void cellChanged(Cell cell);
	void isSolvingChanged(bool isSolving);
	
private:
	void doJob();
	WholeField wholeField;
	QVector<std::shared_ptr<AbstractLineSolver>> lineSolvers;
	bool solving = false;
	int x = 0;
	int y = 0;
};

#endif // SOLVERWORKER_H
