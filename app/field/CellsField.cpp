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
#include "CellsField.h"
#include <QDebug>


CellsField::CellsField(int width, int height) : array(width, height)
{
	qDebug() << "DrawingAreaField width height c-tor";
}

CellsField::~CellsField()
{
	qDebug() << "DrawingAreaField d-tor";
}

Cell CellsField::getCell(AddressOfCell address) const
{
	int x = address.getX();
	int y = address.getY();
	return array.getPixelAt(x, y);
}

void CellsField::setCell(Cell cell)
{
	int x = cell.getAddress().getX();
	int y = cell.getAddress().getY();
	array(x, y) = cell;
	emit cellChanged(cell.getAddress());
}
