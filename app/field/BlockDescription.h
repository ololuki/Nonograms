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
#ifndef BLOCKDESCRIPTION_H
#define BLOCKDESCRIPTION_H

#include "AddressOnBlocksDescription.h"
#include "pixelSign.h"


///
/// \brief BlockDescription class contains one block description (number) of picture (field). 
/// Sign is for future use - every block is currently black.
///
class BlockDescription
{
public:
	BlockDescription(AddressOnBlocksDescription address, int blockSize, pixelSign sign = pixelSign::SGN_FILL_BLACK)
		: address(address), blockSize(blockSize), sign(sign) {}
	int getBlockSize() {return blockSize;}
	void setBlockSize(int blockSize) {this->blockSize = blockSize;}
	bool isFilledBlack(){return sign == pixelSign::SGN_FILL_BLACK;}
	void makeFilledBlack() {sign = pixelSign::SGN_FILL_BLACK;}
	AddressOnBlocksDescription getAddress() {return address;}
	void updateAddress(AddressOnBlocksDescription newAddress) {address = newAddress;}
private:
	AddressOnBlocksDescription address;
	int blockSize;
	pixelSign sign;
};

#endif // BLOCKDESCRIPTION_H
