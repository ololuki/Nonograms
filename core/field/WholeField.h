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
#ifndef WHOLEFIELD_H
#define WHOLEFIELD_H

#include <memory>
#include "CellsField.h"
#include "HintsField.h"


///
/// \brief WholeField is simple class contains whole data about Field.
/// It has data of field parts: drawing area, columns hints
/// and rows hints.
///
class WholeField
{
public:
	WholeField();
	WholeField(int width, int height);
	WholeField(CellsField cells, HintsField columns, HintsField rows);
	WholeField(const WholeField &field);
	WholeField& operator=(const WholeField& field);
	WholeField& operator=(WholeField&& field);
	virtual ~WholeField();
	bool operator==(const WholeField& other) const;
	bool operator!=(const WholeField& other) const;
	int getWidth() const;
	int getHeight() const;
	CellsField& cells();
	HintsField& columnsHints();
	HintsField& rowsHints();
	const CellsField& cells() const;
	const HintsField& columnsHints() const;
	const HintsField& rowsHints() const;
	void clearDrawingArea();
	void clearBlocksDescription();
private:
	int width;
	int height;
	CellsField cellsField;
	HintsField columnsHintsField;
	HintsField rowsHintsField;
};

Q_DECLARE_METATYPE(WholeField)

#endif // WHOLEFIELD_H
