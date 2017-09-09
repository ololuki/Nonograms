/**********************************************************************
 * Copyright (C) 2017 Ololuki
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
#ifndef FIELDMODE_H
#define FIELDMODE_H

///
/// \brief The FieldMode enum contains modes of user interaction
/// with models
///
enum class FieldMode
{
	// drawing area is active for user - can be painted
	FreeDrawingMode,
	
	// columns descriptions are active - user can defining block sizes
	DefiningMode,
	
	// drawing area and blocks description are inactive for user
	// autosolver can be used to solve nonogram
	AutoSolvingMode,
	
	// drawing area is active for user
	// user can solve nonogram
	HumanSolvingMode
};

#endif // FIELDMODE_H
