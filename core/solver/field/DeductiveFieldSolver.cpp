/**********************************************************************
 * Copyright (C) 2017-2021 Ololuki
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
#include "DeductiveFieldSolver.h"
#include "solver/line/BlocksFromBordersSolver.h"
#include "solver/line/BlocksFromDotAndFilledSolver.h"
#include "solver/line/CoveringBlocksSolver.h"
#include "solver/line/DotsBetweenDotsSolver.h"
#include "solver/line/FillFinishedSolver.h"
#include "solver/line/SingleDotsAroundFinishedBlocksSolver.h"


DeductiveFieldSolver::DeductiveFieldSolver()
{
	std::shared_ptr<AbstractLineSolver> solver;

	solver = std::make_shared<BlocksFromBordersSolver>();
	lineSolvers.push_back(solver);
	solver = std::make_shared<BlocksFromDotAndFilledSolver>();
	lineSolvers.push_back(solver);
	solver = std::make_shared<CoveringBlocksSolver>();
	lineSolvers.push_back(solver);
	solver = std::make_shared<DotsBetweenDotsSolver>();
	lineSolvers.push_back(solver);
	solver = std::make_shared<FillFinishedSolver>();
	lineSolvers.push_back(solver);
	solver = std::make_shared<SingleDotsAroundFinishedBlocksSolver>();
	lineSolvers.push_back(solver);
}

void DeductiveFieldSolver::setWholeField(WholeField wholeField)
{
	this->wholeField = wholeField;
}

void DeductiveFieldSolver::solveOneStep()
{
	for (int row = 0; row < wholeField.getHeight(); row++)
	{
		LineOfHints hints = wholeField.rowsHints().getLineOfHints(row);
		LineOfCells lineOfCells = wholeField.cells().getLineOfCells(row, Orientation::HORIZONTAL);
		for (std::shared_ptr<AbstractLineSolver> s : lineSolvers)
		{
			s->solve(hints, lineOfCells);
			wholeField.cells().setLineOfCells(lineOfCells);
			for (int i = 0; i < lineOfCells.size(); i++)
			{
				notifyCellChanged(Cell(lineOfCells.at(i)));
			}
		}
	}

	for (int col = 0; col < wholeField.getWidth(); col++)
	{
		LineOfHints hints = wholeField.columnsHints().getLineOfHints(col);
		LineOfCells lineOfCells = wholeField.cells().getLineOfCells(col, Orientation::VERTICAL);
		for (std::shared_ptr<AbstractLineSolver> s : lineSolvers)
		{
			s->solve(hints, lineOfCells);
			wholeField.cells().setLineOfCells(lineOfCells);
			for (int i = 0; i < lineOfCells.size(); i++)
			{
				notifyCellChanged(Cell(lineOfCells.at(i)));
			}
		}
	}

	state = State::finished;
}

AbstractFieldSolver::State DeductiveFieldSolver::getState()
{
	return state;
}
