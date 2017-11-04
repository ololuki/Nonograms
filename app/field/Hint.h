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
#ifndef HINT_H
#define HINT_H

#include "AddressOfHint.h"
#include "cellSign.h"


///
/// \brief Hint class contains one block description (number) of picture (field).
/// Sign is for future use - every block is currently black.
///
class Hint
{
public:
	Hint(AddressOfHint address, int blockSize, cellSign sign = cellSign::SGN_FILL_BLACK)
		: address(address), blockSize(blockSize), sign(sign) {}
	int getBlockSize() {return blockSize;}
	void setBlockSize(int blockSize) {this->blockSize = blockSize;}
	bool isFilledBlack() {return sign == cellSign::SGN_FILL_BLACK;}
	void makeFilledBlack() {sign = cellSign::SGN_FILL_BLACK;}
	AddressOfHint getAddress() {return address;}
	void updateAddress(AddressOfHint newAddress) {address = newAddress;}
private:
	AddressOfHint address;
	int blockSize;
	cellSign sign;
};

#endif // HINT_H
