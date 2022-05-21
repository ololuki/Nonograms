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
#include "DeductiveFieldSolver.h"
#include "solver/line/BlocksFromBordersSolver.h"
#include "solver/line/BlocksFromDotAndFilledSolver.h"
#include "solver/line/CoveringBlocksSolver.h"
#include "solver/line/DotsBetweenDotsSolver.h"
#include "solver/line/FillFinishedSolver.h"
#include "solver/line/SingleDotsAroundFinishedBlocksSolver.h"
#include "splitter/FinishedBlocksLineSplitter.h"


DeductiveFieldSolver::DeductiveFieldSolver()
{
	lineSolvers.push_back(std::make_unique<const BlocksFromBordersSolver>());
	lineSolvers.push_back(std::make_unique<const BlocksFromDotAndFilledSolver>());
	lineSolvers.push_back(std::make_unique<const CoveringBlocksSolver>());
	lineSolvers.push_back(std::make_unique<const DotsBetweenDotsSolver>());
	lineSolvers.push_back(std::make_unique<const FillFinishedSolver>());
	lineSolvers.push_back(std::make_unique<const SingleDotsAroundFinishedBlocksSolver>());

	lineSplitters.push_back(std::make_unique<const FinishedBlocksLineSplitter>());
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

		for (const auto& s : lineSolvers)
		{
			LineOfCells lineOfCells = wholeField.cells().getLineOfCells(row, Orientation::HORIZONTAL);

			s->solve(hints, lineOfCells);
			wholeField.cells().setLineOfCells(lineOfCells);
			for (int i = 0; i < lineOfCells.size(); i++)
			{
				notifyCellChanged(Cell(lineOfCells.at(i)));
			}

			for (const auto& splitter : lineSplitters)
			{
				auto list = splitter->split(hints, lineOfCells);
				for (auto& subline : list)
				{
					s->solve(subline.lineOfHints, subline.lineOfCells);
					wholeField.cells().setLineOfCells(subline.lineOfCells, Orientation::HORIZONTAL, row, subline.offset);
					for (int i = 0; i < lineOfCells.size(); i++)
					{
						notifyCellChanged(Cell(lineOfCells.at(i)));
					}
				}
			}
		}
	}

	for (int col = 0; col < wholeField.getWidth(); col++)
	{
		LineOfHints hints = wholeField.columnsHints().getLineOfHints(col);

		for (const auto& s : lineSolvers)
		{
			LineOfCells lineOfCells = wholeField.cells().getLineOfCells(col, Orientation::VERTICAL);

			s->solve(hints, lineOfCells);
			wholeField.cells().setLineOfCells(lineOfCells);
			for (int i = 0; i < lineOfCells.size(); i++)
			{
				notifyCellChanged(Cell(lineOfCells.at(i)));
			}

			for (const auto& splitter : lineSplitters)
			{
				auto list = splitter->split(hints, lineOfCells);
				for (auto& subline : list)
				{
					s->solve(subline.lineOfHints, subline.lineOfCells);
					wholeField.cells().setLineOfCells(subline.lineOfCells, Orientation::VERTICAL, col, subline.offset);
					for (int i = 0; i < lineOfCells.size(); i++)
					{
						notifyCellChanged(Cell(lineOfCells.at(i)));
					}
				}
			}
		}
	}

	state = State::finished;
}

AbstractFieldSolver::State DeductiveFieldSolver::getState()
{
	return state;
}
