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
#ifndef ABSTRACTFIELDSOLVER_H
#define ABSTRACTFIELDSOLVER_H

#include <list>
#include <memory>
#include "field/Cell.h"
#include "field/WholeField.h"
class FieldSolverObserver;


class AbstractFieldSolver
{
public:
	enum State
	{
		notStarted,
		solving,
		finished
	};

	AbstractFieldSolver() = default;
	virtual ~AbstractFieldSolver() = default;

	/// set WholeField with defined Hints
	virtual void setWholeField(WholeField wholeField) = 0;

	/// solve one step - this function should be short and invoked in loop
	/// with checking for State::finished
	virtual void solveOneStep() = 0;

	virtual State getState() = 0;

	void registerObserver(FieldSolverObserver* observer);
	void unregisterObserver(FieldSolverObserver* observer);

protected:
	/// notify observers that Cell was resolved
	void notifyCellChanged(Cell cell);

private:
	std::list<FieldSolverObserver*> observers;
};

Q_DECLARE_METATYPE(std::shared_ptr<AbstractFieldSolver>)

#endif // ABSTRACTFIELDSOLVER_H
