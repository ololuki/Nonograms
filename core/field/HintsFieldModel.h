/**********************************************************************
 * Copyright (C) 2017 - 2019 Ololuki
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
#ifndef HINTSFIELDMODEL_H
#define HINTSFIELDMODEL_H

#include <QObject>
#include "AddressOfHint.h"
#include "Hint.h"
#include "LineOfHints.h"
#include "utils/NVector.h"


///
/// \brief HintsFieldModel class is model class of
/// blocks description data (columns hints and rows hints)
/// HintsFieldModels are part of WholeFieldModel.
/// WholeFieldModel contains two instances of HintsFieldModels
/// - one for columns and one for rows.
///
class HintsFieldModel : public QObject
{
	Q_OBJECT
public:
	HintsFieldModel(int numberOfLines, Orientation o);
	~HintsFieldModel();
	Hint getHint(AddressOfHint address) const;
	void updateHint(Hint hint);
	void insertHintBefore(Hint hint);
	void addHintAtEnd(Hint hint);
	void deleteHint(Hint hint);

	int numberOfBlocksInLine(int lineNumber) const;
	int getNumberOfLines() const;
	int allHintsLength() const;
	Orientation getOrientation() const;

	bool isDefinedHintAt(AddressOfHint address) const;

	LineOfHints getLineOfHints(int lineNumber);
	void setLineOfHints(LineOfHints line);
signals:
	void lineOfHintsChanged(int lineNumber, Orientation orientation);
private:
	int numberOfLines;
	Orientation orientation;
	NVector<LineOfHints> linesOfHints;
};

#endif // HINTSFIELDMODEL_H
