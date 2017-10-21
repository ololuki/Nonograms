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


BlocksDescriptionField::BlocksDescriptionField(int numberOfLines, AddressOnBlocksDescription::orientation o)
{
	this->numberOfLines = numberOfLines;
	this->orientation = o;
	const int defaultBlockSize = 0;
	for(int i = 0; i < numberOfLines; i++)
	{
		AddressOnBlocksDescription address = AddressOnBlocksDescription(orientation, i, 0);
		NVector<BlockDescription> line;
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
	int line = blockDescription.getAddress().getLine();
	linesOfHints[line].updateBlockDescription(blockDescription);
	emit blocksDescriptionChanged();
}

void BlocksDescriptionField::insertDescriptionBefore(BlockDescription blockDescription)
{
	int line = blockDescription.getAddress().getLine();
	linesOfHints[line].insertDescriptionBefore(blockDescription);
	emit blocksDescriptionChanged();
}

void BlocksDescriptionField::addDescriptionAtEnd(BlockDescription blockDescription)
{
	int line = blockDescription.getAddress().getLine();
	int count = blockDescription.getAddress().getCount();
	if (linesOfHints[line].size() == count)
	{
		linesOfHints[line].push_back(blockDescription);
	}
	emit blocksDescriptionChanged();
}

void BlocksDescriptionField::deleteDescription(BlockDescription blockDescription)
{
	int line = blockDescription.getAddress().getLine();
	int count = blockDescription.getAddress().getCount();
	if (linesOfHints[line].size() <= 1) return;
	int newLength = linesOfHints[line].size() - 1;
	for(int i = count; i < newLength; i++)
	{
		linesOfHints[line][i].setBlockSize( linesOfHints[line][i+1].getBlockSize());
	}
	linesOfHints[line].pop_back();
	emit blocksDescriptionChanged();
}

int BlocksDescriptionField::numberOfBlocksInLine(int lineNumber)
{
	return linesOfHints[lineNumber].size();
}

int BlocksDescriptionField::getNumberOfLines() const
{
	return numberOfLines;
}

int BlocksDescriptionField::allBlocksDescriptionLength()
{
	int length = 0;
	for (int i = 0; i < numberOfLines; i++)
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
	int line = address.getLine();
	if (line >= linesOfHints.size()) return false;
	if (address.getCount() >= linesOfHints[line].size()) return false;
	return true;
}
