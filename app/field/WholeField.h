/**********************************************************************
 * Copyright (C) 2017-2018 Ololuki
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
#include <QMetaType>


///
/// \brief WholeField class contains whole data about Field.
/// It has models of field parts: drawing area, columns hints
/// and rows hints.
///
class WholeField
{
public:
	WholeField(int width, int height);
	WholeField(const WholeField &field);
	virtual ~WholeField();
	int getWidth() const;
	int getHeight() const;
	std::shared_ptr<CellsField> cells();
	std::shared_ptr<HintsField> columnsHints();
	std::shared_ptr<HintsField> rowsHints();
	void clearDrawingArea();
	void clearBlocksDescription();
private:
	int width;
	int height;
	std::shared_ptr<CellsField> cellsField;
	std::shared_ptr<HintsField> columnsHintsField;
	std::shared_ptr<HintsField> rowsHintsField;
};

Q_DECLARE_METATYPE(std::shared_ptr</*const*/ WholeField>)

#endif // WHOLEFIELD_H
