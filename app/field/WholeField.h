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
#ifndef WHOLEFIELD_H
#define WHOLEFIELD_H

#include <memory>
#include "DrawingAreaField.h"
#include "BlocksDescriptionField.h"


///
/// \brief WholeField class contains whole data about Field.
/// It has models of field parts: drawing area, columns description
/// and rows descriptions.
///
class WholeField
{
public:
	WholeField(size_t width, size_t height);
	WholeField(const WholeField &field);
	virtual ~WholeField();
	size_t getWidth() const;
	size_t getHeight() const;
	std::shared_ptr<DrawingAreaField> drawingArea();
	std::shared_ptr<BlocksDescriptionField> columnsDescription();
	std::shared_ptr<BlocksDescriptionField> rowsDescription();
	void clearDrawingArea();
	void clearBlocksDescription();
private:
	size_t width;
	size_t height;
	std::shared_ptr<DrawingAreaField> drawingAreaField;
	std::shared_ptr<BlocksDescriptionField> columnsDescriptionField;
	std::shared_ptr<BlocksDescriptionField> rowsDescriptionField;
};

#endif // WHOLEFIELD_H
