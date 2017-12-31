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
#include "CellsFieldTest.h"


void CellsFieldTest::getLineOfCells_should_return_valid_line_check_horizontal()
{
	QSharedPointer<CellsField> field = makeFilledCellsField();
	
	LineOfCells line = field->getLineOfCells(lineNumber, Orientation::HORIZONTAL);
	
	QVERIFY(line.getCellAt(0) == cell01);
	QVERIFY(line.getCellAt(1) == cell11);
	QVERIFY(line.getCellAt(2) == cell21);
	QVERIFY(line.getCellAt(0).getAddress() == address01);
	QVERIFY(line.getCellAt(1).getAddress() == address11);
	QVERIFY(line.getCellAt(2).getAddress() == address21);
}

void CellsFieldTest::getLineOfCells_should_return_valid_line_check_vertical()
{
	QSharedPointer<CellsField> field = makeFilledCellsField();
	
	LineOfCells line = field->getLineOfCells(lineNumber, Orientation::VERTICAL);
	
	QVERIFY(line.getCellAt(0) == cell10);
	QVERIFY(line.getCellAt(1) == cell11);
	QVERIFY(line.getCellAt(0).getAddress() == address10);
	QVERIFY(line.getCellAt(1).getAddress() == address11);
}

void CellsFieldTest::setLineOfCells_should_change_cells_check_horizontal()
{
	QSharedPointer<CellsField> field = makeEmptyCellsField();
	LineOfCells line = LineOfCells({cell01, cell11, cell21});
	
	field->setLineOfCells(line);
	
	QVERIFY(field->getCell(address01) == cell01);
	QVERIFY(field->getCell(address11) == cell11);
	QVERIFY(field->getCell(address21) == cell21);
}

void CellsFieldTest::signals_cellChanged_should_be_emited_only_for_cells_changed_by_setLineOfCells()
{
	QSharedPointer<CellsField> field = makeFilledCellsField();
	
	QSignalSpy spy(field.data(), &CellsField::cellChanged);
	
	LineOfCells line = field->getLineOfCells(lineNumber, Orientation::HORIZONTAL);
	line[1].makeFilledBlack();
	QVERIFY2(line[1] != cell11, "Ensure cell changed");
	field->setLineOfCells(line);
	
	const int NUMBER_OF_CELLS_CHANGED = 1;
	QCOMPARE(spy.count(), NUMBER_OF_CELLS_CHANGED);
	QVERIFY(qvariant_cast<AddressOfCell>(spy.takeFirst().at(0)) == address11);
}

QSharedPointer<CellsField> CellsFieldTest::makeEmptyCellsField()
{
	return QSharedPointer<CellsField>(new CellsField(width, height));
}

QSharedPointer<CellsField> CellsFieldTest::makeFilledCellsField()
{
	QSharedPointer<CellsField> field = makeEmptyCellsField();
	field->setCell(cell01);
	field->setCell(cell10);
	field->setCell(cell11);
	field->setCell(cell21);
	return field;
}
