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
#ifndef ADDRESSOFHINT_H
#define ADDRESSOFHINT_H

#include "Orientation.h"


///
/// \brief Contains address of every Block Description (hint) on BlocksDescriptionField
/// address counts from top do bottom
/// and from left to right
///
class AddressOfHint
{
public:
	AddressOfHint();
	AddressOfHint(Orientation o, int line, int count);
	bool isValid() const;
	int getLine() const {return line;}
	int getCount() const {return count;}
	Orientation getOrientation() const {return o;}
	bool isColumn() const {return o == Orientation::VERTICAL;}
	bool isRow() const {return o == Orientation::HORIZONTAL;}
	bool operator==(const AddressOfHint &address) const {
		return (this->line == address.line && this->count == address.count && this->o == address.o);
	}
	bool operator!=(const AddressOfHint &address) const {
		return (this->line != address.line || this->count != address.count || this->o != address.o);
	}
private:
	Orientation o;
	int line;
	int count;
};

#endif // ADDRESSOFHINT_H
