/**********************************************************************
 * Copyright (C) 2017 - 2022 Ololuki
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

#include <string>
#include "utils/NVector.h"
#include "field/Hint.h"

///
/// \brief LineOfHints contains Hints (blocks descriptions) for one line of picture
///
class LineOfHints
{
public:
	typedef typename NVector<Hint>::iterator iterator;
	typedef typename NVector<Hint>::const_iterator const_iterator;
	typedef typename NVector<Hint>::reverse_iterator reverse_iterator;
	typedef typename NVector<Hint>::const_reverse_iterator const_reverse_iterator;

	LineOfHints();
	LineOfHints(NVector<Hint> vectorToCopy);

	LineOfHints(const LineOfHints&) = default;
	LineOfHints(LineOfHints&&) = default;
	LineOfHints& operator=(const LineOfHints&) = default;
	LineOfHints& operator=(LineOfHints&&) = default;
	~LineOfHints() = default;

	int size() const;
	
	void updateHint(Hint hint);
	void insertHintBefore(Hint hint);
	void addHintAtEnd(Hint hint);
	void deleteHint(Hint hint);
	
	Hint& operator[](int count);
	const Hint& operator[](int count) const;
	Hint& front();
	const Hint& front() const;
	Hint& back();
	const Hint& back() const;

	iterator begin() {return hints.begin();}
	const_iterator begin() const {return hints.begin();}
	const_iterator cbegin() const {return hints.cbegin();}

	iterator end() {return hints.end();}
	const_iterator end() const {return hints.end();}
	const_iterator cend() const {return hints.cend();}

	reverse_iterator rbegin() {return hints.rbegin();}
	const_reverse_iterator rbegin() const {return hints.rbegin();}
	const_reverse_iterator crbegin() const {return hints.crbegin();}

	reverse_iterator rend() {return hints.rend();}
	const_reverse_iterator rend() const {return hints.rend();}
	const_reverse_iterator crend() const {return hints.crend();}

	void push_back(Hint hint);
	void pop_back();

	bool operator==(const LineOfHints& other) const;
	bool operator!=(const LineOfHints& other) const;

	std::string toStdString() const;
private:
	NVector<Hint> hints;
};

char* toString(const LineOfHints& cells);

Q_DECLARE_METATYPE(LineOfHints)

#endif // LINEOFHINTS_H
