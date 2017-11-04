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


BlocksDescriptionField::BlocksDescriptionField(int numberOfLines, AddressOfHint::orientation o)
{
	this->numberOfLines = numberOfLines;
	this->orientation = o;
	const int defaultBlockSize = 0;
	for(int i = 0; i < numberOfLines; i++)
	{
		AddressOfHint address = AddressOfHint(orientation, i, 0);
		NVector<Hint> line;
		line.push_back(Hint(address, defaultBlockSize));
		linesOfHints.push_back(line);
	}
}

BlocksDescriptionField::~BlocksDescriptionField()
{
	
}

Hint BlocksDescriptionField::getHint(AddressOfHint address) const
{
	return linesOfHints[address.getLine()][address.getCount()];
}

void BlocksDescriptionField::updateHint(Hint hint)
{
	int line = hint.getAddress().getLine();
	linesOfHints[line].updateHint(hint);
	emit hintChanged();
}

void BlocksDescriptionField::insertHintBefore(Hint hint)
{
	int line = hint.getAddress().getLine();
	linesOfHints[line].insertHintBefore(hint);
	emit hintChanged();
}

void BlocksDescriptionField::addHintAtEnd(Hint hint)
{
	int line = hint.getAddress().getLine();
	int count = hint.getAddress().getCount();
	if (linesOfHints[line].size() == count)
	{
		linesOfHints[line].push_back(hint);
	}
	emit hintChanged();
}

void BlocksDescriptionField::deleteHint(Hint hint)
{
	int line = hint.getAddress().getLine();
	int count = hint.getAddress().getCount();
	if (linesOfHints[line].size() <= 1) return;
	int newLength = linesOfHints[line].size() - 1;
	for(int i = count; i < newLength; i++)
	{
		linesOfHints[line][i].setBlockSize(linesOfHints[line][i+1].getBlockSize());
	}
	linesOfHints[line].pop_back();
	emit hintChanged();
}

int BlocksDescriptionField::numberOfBlocksInLine(int lineNumber) const
{
	return linesOfHints[lineNumber].size();
}

int BlocksDescriptionField::getNumberOfLines() const
{
	return numberOfLines;
}

int BlocksDescriptionField::allHintsLength() const
{
	int length = 0;
	for (int i = 0; i < numberOfLines; i++)
	{
		length = (numberOfBlocksInLine(i) > length) ? numberOfBlocksInLine(i) : length;
	}
	return length;
}

AddressOfHint::orientation BlocksDescriptionField::getOrientation() const
{
	return orientation;
}

bool BlocksDescriptionField::isDefinedHintAt(AddressOfHint address) const
{
	int line = address.getLine();
	if (line >= linesOfHints.size()) return false;
	if (address.getCount() >= linesOfHints[line].size()) return false;
	return true;
}
