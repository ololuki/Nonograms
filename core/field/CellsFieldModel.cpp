/**********************************************************************
 * Copyright (C) 2017 - 2022 Ololuki
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
#include "CellsFieldModel.h"
#include <QDebug>


CellsFieldModel::CellsFieldModel(int width, int height) : CellsField(width, height)
{
	qDebug() << "CellsFieldModel width height c-tor";
}

CellsFieldModel::~CellsFieldModel()
{
	qDebug() << "CellsFieldModel d-tor";
}

void CellsFieldModel::setCell(Cell cell)
{
	if (cell.getAddress().isValid())
	{
		int x = cell.getAddress().getX();
		int y = cell.getAddress().getY();
		if (array(x, y) != cell)
		{
			array(x, y) = cell;
			emit cellChanged(cell.getAddress());
		}
	}
}

/// returns CellsField - simply object, that not derives from QObject
/// and is copyable
CellsField CellsFieldModel::getCellsField() const
{
	return (CellsField(*this));
}

/// set internal contents of this to be equal with given field
void CellsFieldModel::setCellsField(CellsField field)
{
	static_cast<CellsField&>(*this) = field;
	emit cellsChanged();
}
