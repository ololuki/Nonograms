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
#ifndef CELLSFIELD_H
#define CELLSFIELD_H

#include <QObject>
#include "AddressOfCell.h"
#include "Orientation.h"
#include "Cell.h"
#include "ArrayOfCells.h"
#include "LineOfCells.h"


///
/// \brief CellsField class is simple class of drawing area data.
/// CellsFieldModel derive from CellsField.
/// CellsField is part of WholeField. WholeField contains CellsField.
///
class CellsField
{
public:
	CellsField();
	CellsField(int width, int height);
	CellsField(const CellsField& field) = default;
	CellsField(std::initializer_list<LineOfCells> rows);
	CellsField& operator=(const CellsField& field) = default;
	CellsField& operator=(CellsField&& field);
	virtual ~CellsField();

	bool areSolvedCellsEqual(const CellsField& other) const;
	int getWidth() const {return array.width();}
	int getHeight() const {return array.height();}
	const Cell& getCell(AddressOfCell address) const;
	virtual void setCell(Cell cell);
	LineOfCells getLineOfCells(int lineNumber, Orientation orientation) const;
	void setLineOfCells(LineOfCells lineOfCells);
	void setLineOfCells(LineOfCells lineOfCells, int lineNumber, Orientation orientation);

protected:
	ArrayOfCells array;
};

#endif // CELLSFIELD_H
