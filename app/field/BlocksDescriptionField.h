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
#ifndef BLOCKSDESCRIPTIONFIELD_H
#define BLOCKSDESCRIPTIONFIELD_H

#include <QObject>
#include "AddressOnBlocksDescription.h"
#include "BlockDescription.h"
#include "LineOfHints.h"
#include "utils/NVector.h"


///
/// \brief BlocksDescriptionField class is model class of
/// blocks description data (columns description and rows description)
/// BlocksDescriptionFields are part of WholeField.
/// WholeField contains two instances of BlocksDescriptionFields
/// - one for columns and one for rows.
///
class BlocksDescriptionField : public QObject
{
	Q_OBJECT
public:
	BlocksDescriptionField(int numberOfLines, AddressOnBlocksDescription::orientation o);
	virtual ~BlocksDescriptionField();
	virtual BlockDescription getBlockDescription(AddressOnBlocksDescription address) const;
	virtual void updateBlockDescription(BlockDescription blockDescription);
	virtual void insertDescriptionBefore(BlockDescription blockDescription);
	virtual void addDescriptionAtEnd(BlockDescription blockDescription);
	virtual void deleteDescription(BlockDescription blockDescription);
	
	virtual int numberOfBlocksInLine(int lineNumber) const;
	virtual int getNumberOfLines() const;
	virtual int allBlocksDescriptionLength() const;
	virtual AddressOnBlocksDescription::orientation getOrientation() const;
	
	virtual bool isDefinedDescriptionAt(AddressOnBlocksDescription address) const;
signals:
	void blocksDescriptionChanged();
private:
	int numberOfLines;
	AddressOnBlocksDescription::orientation orientation;
	NVector<LineOfHints> linesOfHints;
};

#endif // BLOCKSDESCRIPTIONFIELD_H
