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
#ifndef HINTSFIELD_H
#define HINTSFIELD_H

#include "AddressOfHint.h"
#include "Hint.h"
#include "LineOfHints.h"
#include "utils/NVector.h"


///
/// \brief HintsField class is simple class of
/// blocks description data (columns hints and rows hints).
/// HintsFieldModel derive from HintsField.
/// HintsFields are part of WholeField.
/// WholeField contains two instances of HintsFields
/// - one for columns and one for rows.
///
class HintsField
{
public:
	HintsField();
	HintsField(int numberOfLines, Orientation o);
	HintsField(const HintsField& hintsField);
	HintsField(Orientation o, std::initializer_list<LineOfHints> lines);
	HintsField& operator=(const HintsField& field) = default;
	HintsField& operator=(HintsField&& field) = default;
	virtual ~HintsField();

	bool operator==(const HintsField& other) const;
	bool operator!=(const HintsField& other) const;

	const Hint& getHint(AddressOfHint address) const;
	virtual void updateHint(Hint hint);
	virtual void insertHintBefore(Hint hint);
	virtual void addHintAtEnd(Hint hint);
	virtual void deleteHint(Hint hint);

	int numberOfBlocksInLine(int lineNumber) const;
	int getNumberOfLines() const;
	int allHintsLength() const;
	Orientation getOrientation() const;

	bool isDefinedHintAt(AddressOfHint address) const;

	LineOfHints getLineOfHints(int lineNumber);
	virtual void setLineOfHints(LineOfHints line);

	std::string toStdString() const;
protected:
	int numberOfLines;
	Orientation orientation;
	NVector<LineOfHints> linesOfHints;
};

char *toString(const HintsField& hints);

#endif // HINTSFIELD_H
