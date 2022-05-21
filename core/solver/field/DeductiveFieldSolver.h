/**********************************************************************
 * Copyright (C) 2017 - 2022 Ololuki
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
#ifndef DEDUCTIVEFIELDSOLVER_H
#define DEDUCTIVEFIELDSOLVER_H

#include "AbstractFieldSolver.h"
#include "field/WholeField.h"
#include "solver/line/AbstractLineSolver.h"
#include "splitter/AbstractLineSplitter.h"
#include <memory>


///
/// \brief Field solver which automatically solves nonogram as human
/// by deduction.
///
class DeductiveFieldSolver : public AbstractFieldSolver
{
public:
	DeductiveFieldSolver();
	~DeductiveFieldSolver() override = default;

	void setWholeField(WholeField wholeField) override;
	void solveOneStep() override;

	const WholeField& getWholeField() const {return wholeField;}
	State getState() override;

private:
	WholeField wholeField;
	State state = State::notStarted;
	std::vector<std::unique_ptr<const AbstractLineSolver>> lineSolvers;
	std::vector<std::unique_ptr<const AbstractLineSplitter>> lineSplitters;
};

#endif // DEDUCTIVEFIELDSOLVER_H
