/**********************************************************************
 * Copyright (C) 2017 - 2021 Ololuki
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
#ifndef LINEOFCELLS_H
#define LINEOFCELLS_H

#include "Cell.h"
#include "vector"
#include "utils/NVector.h"


///
/// \brief LineOfCells stores one line of Cells.
/// Orientation of the line (horizontal or vertical) is arbitrary.
/// Cells are accesible by operator[].
///
class LineOfCells
{
public:
	typedef typename NVector<Cell>::iterator iterator;
	typedef typename NVector<Cell>::const_iterator const_iterator;
	typedef typename NVector<Cell>::reverse_iterator reverse_iterator;
	typedef typename NVector<Cell>::const_reverse_iterator const_reverse_iterator;

	LineOfCells();
	LineOfCells(QString str);
	LineOfCells(NVector<Cell> vectorToCopy);
	int size() const;
	
	Cell& at(int cellNumber);
	const Cell& at(int cellNumber) const;
	Cell& operator[](int cellNumber);
	Cell& front();
	const Cell& front() const;
	Cell& back();
	const Cell& back() const;

	iterator begin() {return cells.begin();}
	const_iterator begin() const {return cells.begin();}
	const_iterator cbegin() const {return cells.cbegin();}

	iterator end() {return cells.end();}
	const_iterator end() const {return cells.end();}
	const_iterator cend() const {return cells.cend();}

	reverse_iterator rbegin() {return cells.rbegin();}
	const_reverse_iterator rbegin() const {return cells.rbegin();}
	const_reverse_iterator crbegin() const {return cells.crbegin();}

	reverse_iterator rend() {return cells.rend();}
	const_reverse_iterator rend() const {return cells.rend();}
	const_reverse_iterator crend() const {return cells.crend();}

	bool operator==(const LineOfCells& other) const;
	bool operator!=(const LineOfCells& other) const;
private:
	NVector<Cell> cells;
};

char* toString(const LineOfCells& cells);

Q_DECLARE_METATYPE(LineOfCells)

#endif // LINEOFCELLS_H
