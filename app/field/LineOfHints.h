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
#ifndef LINEOFHINTS_H
#define LINEOFHINTS_H

#include <vector>
#include "utils/NVector.h"
#include "field/Hint.h"

///
/// \brief LineOfHints contains Hints (blocks descriptions) for one line of picture
///
class LineOfHints
{
public:
	LineOfHints(NVector<Hint> vectorToCopy);
	int size() const;
	
	void updateHint(Hint hint);
	void insertHintBefore(Hint hint);
	void addHintAtEnd(Hint hint);
	void deleteHint(Hint hint);
	
	Hint& operator[](int count);
	const Hint& operator[](int count) const;
	void push_back(Hint hint);
	void pop_back();
private:
	NVector<Hint> hints;
};

#endif // LINEOFHINTS_H
