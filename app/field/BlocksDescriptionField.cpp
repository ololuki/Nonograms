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
	allLinesDescription = AllLinesDescription(o, numberOfLines);
}

BlocksDescriptionField::~BlocksDescriptionField()
{
	
}

BlockDescription BlocksDescriptionField::getBlockDescription(AddressOnBlocksDescription address)
{
	return allLinesDescription(address.getLine(), address.getCount());
}

void BlocksDescriptionField::updateBlockDescription(BlockDescription blockDescription)
{
	allLinesDescription.updateDescription(blockDescription);
	emit blocksDescriptionChanged();
}

void BlocksDescriptionField::insertDescriptionBefore(BlockDescription blockDescription)
{
	allLinesDescription.insertDescriptionBefore(blockDescription);
	emit blocksDescriptionChanged();
}

void BlocksDescriptionField::addDescriptionAtEnd(BlockDescription blockDescription)
{
	allLinesDescription.addDescriptionAtEnd(blockDescription);
	emit blocksDescriptionChanged();
}

void BlocksDescriptionField::deleteDescription(BlockDescription blockDescription)
{
	allLinesDescription.deleteDescription(blockDescription);
	emit blocksDescriptionChanged();
}

size_t BlocksDescriptionField::numberOfBlocksInLine(size_t lineNumber)
{
	return allLinesDescription.numberOfBlocksInLine(lineNumber);
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
	return allLinesDescription.isDefinedDescriptionAt(address.getLine(), address.getCount());
}
