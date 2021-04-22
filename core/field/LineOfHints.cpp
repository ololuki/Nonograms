/**********************************************************************
 * Copyright (C) 2017 - 2021 Ololuki
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


///
/// \brief Makes invalid, empty vector of Hints.
/// Used to support data driven tests.
///
LineOfHints::LineOfHints()
{
	
}

LineOfHints::LineOfHints(NVector<Hint> vectorToCopy)
	: hints(vectorToCopy)
{
}

int LineOfHints::size() const
{
	return static_cast<int>(hints.size());
}

void LineOfHints::updateHint(Hint hint)
{
	AddressOfHint address = hint.getAddress();
	int count = address.getCount();
	if (count >= hints.size()) return;
	if (hints[count].getAddress() != address) return;
	hints[count] = hint;
}

void LineOfHints::insertHintBefore(Hint hint)
{
	int line = hint.getAddress().getLine();
	int count = hint.getAddress().getCount();
	int length = hints.size();
	Orientation orientation = hint.getAddress().getOrientation();
	if (count >= length) return;
	
	AddressOfHint addressOfNewLast = AddressOfHint(orientation, line, length);
	
	int indexOfCurrentLastBlock = length - 1;
	Hint newLastBlock = hints[indexOfCurrentLastBlock];
	newLastBlock.updateAddress(addressOfNewLast);
	hints.push_back(newLastBlock);
	
	for (int i = length; i-- > count + 1;)
	{
		hints[i].setBlockSize(hints[i-1].getBlockSize());
	}
	hints[count] = hint;
}

Hint &LineOfHints::operator[](int count)
{
	return hints.operator[](static_cast<size_t>(count));
}

const Hint &LineOfHints::operator[](int count) const
{
	return hints.operator[](static_cast<size_t>(count));
}

Hint& LineOfHints::front()
{
	return hints.front();
}

const Hint& LineOfHints::front() const
{
	return hints.front();
}

Hint& LineOfHints::back()
{
	return hints.back();
}

const Hint& LineOfHints::back() const
{
	return hints.back();
}

void LineOfHints::push_back(Hint hint)
{
	hints.push_back(hint);
}

void LineOfHints::pop_back()
{
	hints.pop_back();
}
