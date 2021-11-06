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
#ifndef DRAWINGMODE_H
#define DRAWINGMODE_H

///
/// Drawing mode of nonogram view, defines controller's behavior
///
enum class DrawingMode
{
	/// User can define cells
	FreeDrawing,

	/// User can define hints
	FieldDefining,

	/// User can solving nonograms by drawing cells
	ManualSolving,

	/// Nonogram is automatically solved by deductive solver
	AutoDeductiveSolving,

	/// Nonogram is automatically solved by brute force solver
	AutoBruteForceSolving
};

#endif // DRAWINGMODE_H
