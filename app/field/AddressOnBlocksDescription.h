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
#ifndef ADDRESSONBLOCKSDESCRIPTION_H
#define ADDRESSONBLOCKSDESCRIPTION_H


///
/// \brief Contains address of every Block Description (number) on BlocksDescriptionField
/// address counts from top do bottom
/// and from left to right
///
class AddressOnBlocksDescription
{
public:
	enum orientation
	{
		HORIZONTAL,
		VERTICAL,
	};
	AddressOnBlocksDescription(orientation o, int line, int count);
	int getLine() {return line;}
	int getCount() {return count;}
	orientation getOrientation() {return o;}
	bool isColumn() {return o == VERTICAL;}
	bool isRow() {return o == HORIZONTAL;}
	bool operator==(const AddressOnBlocksDescription &address) const {
		return (this->line == address.line && this->count == address.count && this->o == address.o);
	}
	bool operator!=(const AddressOnBlocksDescription &address) const {
		return (this->line != address.line || this->count != address.count || this->o != address.o);
	}
private:
	orientation o;
	int line;
	int count;
};

#endif // ADDRESSONBLOCKSDESCRIPTION_H
