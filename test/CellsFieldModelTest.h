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
#ifndef CELLSFIELDTEST_H
#define CELLSFIELDTEST_H

#include <QtTest>
#include "field/CellsFieldModel.h"


class CellsFieldModelTest : public QObject
{
	Q_OBJECT
private slots:
	void getLineOfCells_should_return_valid_line_check_horizontal();
	void getLineOfCells_should_return_valid_line_check_vertical();
	void setLineOfCells_should_change_cells_check_horizontal();
	void setCell_with_empty_address_should_not_change_any_Cell();
	void setCell_with_empty_address_should_not_emit_cellChanged();
	void signals_cellChanged_should_be_emited_only_for_cells_changed_by_setLineOfCells();

private:
	const int width = 3;
	const int height = 2;
	const int lineNumber = 1;
	const AddressOfCell address00 = {0, 0};
	const AddressOfCell address01 = {0, 1};
	const AddressOfCell address10 = {1, 0};
	const AddressOfCell address11 = {1, 1};
	const AddressOfCell address20 = {2, 0};
	const AddressOfCell address21 = {2, 1};
	const Cell cell01 = {address01, cellSign::SGN_FILL_BLACK};
	const Cell cell10 = {address10, cellSign::SGN_DOT};
	const Cell cell11 = {address11, cellSign::SGN_EMPTY};
	const Cell cell21 = {address21, cellSign::SGN_DOT};
	QSharedPointer<CellsFieldModel> makeEmptyCellsField();
	QSharedPointer<CellsFieldModel> makeFilledCellsField();
};

#endif // CELLSFIELDTEST_H
