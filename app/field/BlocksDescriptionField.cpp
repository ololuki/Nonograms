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


BlocksDescriptionField::BlocksDescriptionField(size_t width, size_t height, AddressOnBlocksDescription::orientation o)
	: width(width),
	  height(height)
{
	if (o == AddressOnBlocksDescription::VERTICAL)
	{
		columnsDescription = AllLinesDescription(AddressOnBlocksDescription::VERTICAL, width);
	} else {
		rowsDescription = AllLinesDescription(AddressOnBlocksDescription::HORIZONTAL, height);
	}
}

BlocksDescriptionField::~BlocksDescriptionField()
{
	
}

BlockDescription BlocksDescriptionField::getBlockDescription(AddressOnBlocksDescription address)
{
	if (address.isColumn())
	{
		return columnsDescription(address.getLine(), address.getCount());
	} else {
		return rowsDescription(address.getLine(), address.getCount());
	}
}

void BlocksDescriptionField::updateBlockDescription(BlockDescription blockDescription)
{
	if (blockDescription.getAddress().isColumn())
	{
		columnsDescription.updateDescription(blockDescription);
	} else {
		rowsDescription.updateDescription(blockDescription);
	}
	emit blocksDescriptionChanged();
}

void BlocksDescriptionField::insertDescriptionBefore(BlockDescription blockDescription)
{
	if (blockDescription.getAddress().isColumn())
	{
		columnsDescription.insertDescriptionBefore(blockDescription);
	} else {
		rowsDescription.insertDescriptionBefore(blockDescription);
	}
	emit blocksDescriptionChanged();
}

void BlocksDescriptionField::addDescriptionAtEnd(BlockDescription blockDescription)
{
	if (blockDescription.getAddress().isColumn())
	{
		columnsDescription.addDescriptionAtEnd(blockDescription);
	} else {
		rowsDescription.addDescriptionAtEnd(blockDescription);
	}
	emit blocksDescriptionChanged();
}

void BlocksDescriptionField::deleteDescription(BlockDescription blockDescription)
{
	if (blockDescription.getAddress().isColumn())
	{
		columnsDescription.deleteDescription(blockDescription);
	} else {
		rowsDescription.deleteDescription(blockDescription);
	}
	emit blocksDescriptionChanged();
}

size_t BlocksDescriptionField::numberOfBlocksInColumn(size_t columnNumber)
{
	return columnsDescription.numberOfBlocksInLine(columnNumber);
}

size_t BlocksDescriptionField::numberOfBlocksInRow(size_t rowNumber)
{
	return rowsDescription.numberOfBlocksInLine(rowNumber);
}

size_t BlocksDescriptionField::getWidth() const
{
	return width;
}

size_t BlocksDescriptionField::getHeight() const
{
	return height;
}

size_t BlocksDescriptionField::columnsDescriptionHeight()
{
	size_t height = 0;
	for (size_t i = 0; i < getWidth(); i++)
	{
		height = std::max(height, columnsDescription.numberOfBlocksInLine(i));
	}
	return height;
}

size_t BlocksDescriptionField::rowsDescriptionWidth()
{
	size_t width = 0;
	for (size_t i = 0; i < getHeight(); i++)
	{
		width = std::max(width, rowsDescription.numberOfBlocksInLine(i));
	}
	return width;
}

bool BlocksDescriptionField::isDefinedColumnDescriptionAt(AddressOnBlocksDescription address)
{
	if (address.isColumn())
	{
		return columnsDescription.isDefinedDescriptionAt(address.getLine(), address.getCount());
	} else {
		return rowsDescription.isDefinedDescriptionAt(address.getLine(), address.getCount());
	}
}
