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
#include "WholeField.h"
#include <QDebug>


WholeField::WholeField(size_t width, size_t height)
	: width(width),
	  height(height)
{
	drawingAreaField = std::make_shared<DrawingAreaField>(width, height);
	columnsDescriptionField = std::make_shared<BlocksDescriptionField>(width, AddressOnBlocksDescription::VERTICAL);
	rowsDescriptionField = std::make_shared<BlocksDescriptionField>(height, AddressOnBlocksDescription::HORIZONTAL);
	qDebug() << "WholeField width height c-tor";
}

WholeField::WholeField(const WholeField &field)
	: width(field.width),
	  height(field.height)
{
	drawingAreaField = field.drawingAreaField;
	columnsDescriptionField = field.columnsDescriptionField;
	rowsDescriptionField = field.rowsDescriptionField;
	qDebug() << "WholeField copy c-tor";
}

WholeField::~WholeField()
{
	qDebug() << "WholeField d-tor";
}

size_t WholeField::getWidth() const
{
	return width;
}

size_t WholeField::getHeight() const
{
	return height;
}

std::shared_ptr<DrawingAreaField> WholeField::drawingArea()
{
	return drawingAreaField;
}

std::shared_ptr<BlocksDescriptionField> WholeField::columnsDescription()
{
	return columnsDescriptionField;
}

std::shared_ptr<BlocksDescriptionField> WholeField::rowsDescription()
{
	return rowsDescriptionField;
}

void WholeField::clearDrawingArea()
{
	for (size_t i = 0; i < getWidth(); i++)
	{
		for (size_t j = 0; j < getHeight(); j++)
		{
			drawingArea()->setPixel(Pixel(AddressOnDrawingArea(i, j)));
		}
	}
}

void WholeField::clearBlocksDescription()
{
	// TODO
}
