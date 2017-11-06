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
#ifndef HINTSFIELD_H
#define HINTSFIELD_H

#include <QObject>
#include "AddressOfHint.h"
#include "Hint.h"
#include "LineOfHints.h"
#include "utils/NVector.h"


///
/// \brief HintsField class is model class of
/// blocks description data (columns hints and rows hints)
/// HintsFields are part of WholeField.
/// WholeField contains two instances of HintsFields
/// - one for columns and one for rows.
///
class HintsField : public QObject
{
	Q_OBJECT
public:
	HintsField(int numberOfLines, AddressOfHint::orientation o);
	virtual ~HintsField();
	virtual Hint getHint(AddressOfHint address) const;
	virtual void updateHint(Hint hint);
	virtual void insertHintBefore(Hint hint);
	virtual void addHintAtEnd(Hint hint);
	virtual void deleteHint(Hint hint);
	
	virtual int numberOfBlocksInLine(int lineNumber) const;
	virtual int getNumberOfLines() const;
	virtual int allHintsLength() const;
	virtual AddressOfHint::orientation getOrientation() const;
	
	virtual bool isDefinedHintAt(AddressOfHint address) const;
signals:
	void hintChanged();
private:
	int numberOfLines;
	AddressOfHint::orientation orientation;
	NVector<LineOfHints> linesOfHints;
};

#endif // HINTSFIELD_H
