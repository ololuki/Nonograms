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
#include "BlocksDescriptionField.h"


BlocksDescriptionField::BlocksDescriptionField(size_t numberOfLines, AddressOnBlocksDescription::orientation o)
{
	this->numberOfLines = numberOfLines;
	this->orientation = o;
	const size_t defaultBlockSize = 0;
	for(size_t i = 0; i < numberOfLines; i++)
	{
		AddressOnBlocksDescription address = AddressOnBlocksDescription(orientation, i, 0);
		std::vector<BlockDescription> line;
		line.push_back(BlockDescription(address, defaultBlockSize));
		linesOfHints.push_back(line);
	}
}

BlocksDescriptionField::~BlocksDescriptionField()
{
	
}

BlockDescription BlocksDescriptionField::getBlockDescription(AddressOnBlocksDescription address)
{
	return linesOfHints[address.getLine()][address.getCount()];
}

void BlocksDescriptionField::updateBlockDescription(BlockDescription blockDescription)
{
	AddressOnBlocksDescription address = blockDescription.getAddress();
	if (address.getCount() >= linesOfHints[address.getLine()].size()) return;
	linesOfHints[address.getLine()][address.getCount()] = blockDescription;
	emit blocksDescriptionChanged();
}

void BlocksDescriptionField::insertDescriptionBefore(BlockDescription blockDescription)
{
	size_t line = blockDescription.getAddress().getLine();
	size_t count = blockDescription.getAddress().getCount();
	size_t length = linesOfHints[line].size();
	AddressOnBlocksDescription::orientation orientation = blockDescription.getAddress().getOrientation();
	if (count >= length) return;
	
	AddressOnBlocksDescription addressOfNewLast = AddressOnBlocksDescription(orientation, line, length);
	
	BlockDescription newLastBlock = linesOfHints[line][length - 1];
	newLastBlock.updateAddress(addressOfNewLast);
	linesOfHints[line].push_back(newLastBlock);
	
	for (size_t i = length; i-- > count + 1;)
	{
		linesOfHints[line][i].setBlockSize( linesOfHints[line][i-1].getBlockSize());
	}
	linesOfHints[line][count] = blockDescription;
	emit blocksDescriptionChanged();
}

void BlocksDescriptionField::addDescriptionAtEnd(BlockDescription blockDescription)
{
	size_t line = blockDescription.getAddress().getLine();
	size_t count = blockDescription.getAddress().getCount();
	if (linesOfHints[line].size() == count)
	{
		linesOfHints[line].push_back(blockDescription);
	}
	emit blocksDescriptionChanged();
}

void BlocksDescriptionField::deleteDescription(BlockDescription blockDescription)
{
	size_t line = blockDescription.getAddress().getLine();
	size_t count = blockDescription.getAddress().getCount();
	if (linesOfHints[line].size() <= 1) return;
	size_t newLength = linesOfHints[line].size() - 1;
	for(size_t i = count; i < newLength; i++)
	{
		linesOfHints[line][i].setBlockSize( linesOfHints[line][i+1].getBlockSize());
	}
	linesOfHints[line].pop_back();
	emit blocksDescriptionChanged();
}

size_t BlocksDescriptionField::numberOfBlocksInLine(size_t lineNumber)
{
	return linesOfHints[lineNumber].size();
}

size_t BlocksDescriptionField::getNumberOfLines() const
{
	return numberOfLines;
}

size_t BlocksDescriptionField::allBlocksDescriptionLength()
{
	size_t length = 0;
	for (size_t i = 0; i < numberOfLines; i++)
	{
		length = std::max(length, numberOfBlocksInLine(i));
	}
	return length;
}

AddressOnBlocksDescription::orientation BlocksDescriptionField::getOrientation()
{
	return orientation;
}

bool BlocksDescriptionField::isDefinedDescriptionAt(AddressOnBlocksDescription address)
{
	size_t line = address.getLine();
	if (line >= linesOfHints.size()) return false;
	if (address.getCount() >= linesOfHints[line].size()) return false;
	return true;
}
