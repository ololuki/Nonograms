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
#ifndef CELLSIGN_H
#define CELLSIGN_H


///
/// \brief cellSign enum class contains available signs for cells (pixels) of picture
///
enum class cellSign
{
	SGN_EMPTY = -1,			// '-' unresolved
	SGN_FILLED = -2,		// '#' filled cell (not used, filled black will be used)
	SGN_DOT = -3,			// '.' cell with no block (white)
	SGN_FILL_BLACK = -4,	// '#' filled with black color
	// numbers 0 to max-int will be used by solver to name cells by number of current block
};

#endif // CELLSIGN_H
