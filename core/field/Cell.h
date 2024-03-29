/**********************************************************************
 * Copyright (C) 2017 - 2018 Ololuki
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
#ifndef CELL_H
#define CELL_H

#include "AddressOfCell.h"
#include "CellSign.h"


///
/// \brief Cell class contains one pixel (box) of picture (field).
/// It has address measured in cells (boxes) and sign to draw.
///
class Cell
{
public:
	Cell(cellSign sign = cellSign::SGN_EMPTY);
	Cell(char symbol);
	Cell(AddressOfCell address, cellSign sign = cellSign::SGN_EMPTY);

	Cell(const Cell&) = default;
	Cell(Cell&&) = default;
	Cell& operator=(const Cell&) = default;
	Cell& operator=(Cell&&) = default;
	~Cell() = default;

	bool isFilledBlack() const {return sign == cellSign::SGN_FILL_BLACK;}
	bool isDot() const {return sign == cellSign::SGN_DOT;}
	bool isEmpty() const {return sign == cellSign::SGN_EMPTY;}
	void makeFilledBlack() {sign = cellSign::SGN_FILL_BLACK;}
	void makeDot(){sign = cellSign::SGN_DOT;}
	void makeEmpty(){sign = cellSign::SGN_EMPTY;}
	cellSign getSign() const;
	AddressOfCell getAddress() const {return address;}
	bool operator==(const Cell &cell) const {
		return (this->sign == cell.sign);
	}
	bool operator!=(const Cell &cell) const {
		return (this->sign != cell.sign);
	}
private:
	AddressOfCell address;
	cellSign sign;
};

Q_DECLARE_METATYPE(Cell)

#endif // CELL_H
