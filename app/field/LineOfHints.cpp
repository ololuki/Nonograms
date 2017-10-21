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
#include "LineOfHints.h"


LineOfHints::LineOfHints(NVector<BlockDescription> vectorToCopy)
	: hints(vectorToCopy)
{
}

int LineOfHints::size()
{
	return static_cast<int>(hints.size());
}

void LineOfHints::updateBlockDescription(BlockDescription blockDescription)
{
	AddressOnBlocksDescription address = blockDescription.getAddress();
	int count = address.getCount();
	if (count >= hints.size()) return;
	if (hints[count].getAddress() != address) return;
	hints[count] = blockDescription;
}

void LineOfHints::insertDescriptionBefore(BlockDescription blockDescription)
{
	int line = blockDescription.getAddress().getLine();
	int count = blockDescription.getAddress().getCount();
	int length = hints.size();
	AddressOnBlocksDescription::orientation orientation = blockDescription.getAddress().getOrientation();
	if (count >= length) return;
	
	AddressOnBlocksDescription addressOfNewLast = AddressOnBlocksDescription(orientation, line, length);
	
	int indexOfCurrentLastBlock = length - 1;
	BlockDescription newLastBlock = hints[indexOfCurrentLastBlock];
	newLastBlock.updateAddress(addressOfNewLast);
	hints.push_back(newLastBlock);
	
	for (int i = length; i-- > count + 1;)
	{
		hints[i].setBlockSize(hints[i-1].getBlockSize());
	}
	hints[count] = blockDescription;
}

BlockDescription &LineOfHints::operator[](const int count)
{
	return hints.operator[](static_cast<size_t>(count));
}

void LineOfHints::push_back(BlockDescription hint)
{
	hints.push_back(hint);
}

void LineOfHints::pop_back()
{
	hints.pop_back();
}
