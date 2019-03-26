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
#include "CellsFieldModelTest.h"


void CellsFieldModelTest::getLineOfCells_should_return_valid_line_check_horizontal()
{
	QSharedPointer<CellsFieldModel> field = makeFilledCellsField();

	LineOfCells line = field->getLineOfCells(lineNumber, Orientation::HORIZONTAL);

	QVERIFY(line.at(0) == cell01);
	QVERIFY(line.at(1) == cell11);
	QVERIFY(line.at(2) == cell21);
	QVERIFY(line.at(0).getAddress() == address01);
	QVERIFY(line.at(1).getAddress() == address11);
	QVERIFY(line.at(2).getAddress() == address21);
}

void CellsFieldModelTest::getLineOfCells_should_return_valid_line_check_vertical()
{
	QSharedPointer<CellsFieldModel> field = makeFilledCellsField();

	LineOfCells line = field->getLineOfCells(lineNumber, Orientation::VERTICAL);

	QVERIFY(line.at(0) == cell10);
	QVERIFY(line.at(1) == cell11);
	QVERIFY(line.at(0).getAddress() == address10);
	QVERIFY(line.at(1).getAddress() == address11);
}

void CellsFieldModelTest::setLineOfCells_should_change_cells_check_horizontal()
{
	QSharedPointer<CellsFieldModel> field = makeEmptyCellsField();
	LineOfCells line = LineOfCells({cell01, cell11, cell21});

	field->setLineOfCells(line);

	QVERIFY(field->getCell(address01) == cell01);
	QVERIFY(field->getCell(address11) == cell11);
	QVERIFY(field->getCell(address21) == cell21);
}

void CellsFieldModelTest::setCell_with_empty_address_should_not_change_any_Cell()
{
	QSharedPointer<CellsFieldModel> field = makeEmptyCellsField();
	Cell cellFilledWithoutAddress;
	cellFilledWithoutAddress.makeFilledBlack();

	field->setCell(cellFilledWithoutAddress);

	Cell emptyCell;
	QVERIFY(field->getCell(address00) == emptyCell);
	QVERIFY(field->getCell(address01) == emptyCell);
	QVERIFY(field->getCell(address10) == emptyCell);
	QVERIFY(field->getCell(address11) == emptyCell);
	QVERIFY(field->getCell(address20) == emptyCell);
	QVERIFY(field->getCell(address21) == emptyCell);
}

void CellsFieldModelTest::setCell_with_empty_address_should_not_emit_cellChanged()
{
	QSharedPointer<CellsFieldModel> field = makeFilledCellsField();

	QSignalSpy spy(field.data(), &CellsFieldModel::cellChanged);

	field->setCell(Cell());

	const int NUMBER_OF_CELLS_CHANGED = 0;
	QCOMPARE(spy.count(), NUMBER_OF_CELLS_CHANGED);
}

void CellsFieldModelTest::signals_cellChanged_should_be_emited_only_for_cells_changed_by_setLineOfCells()
{
	QSharedPointer<CellsFieldModel> field = makeFilledCellsField();

	QSignalSpy spy(field.data(), &CellsFieldModel::cellChanged);

	LineOfCells line = field->getLineOfCells(lineNumber, Orientation::HORIZONTAL);
	line[1].makeFilledBlack();
	QVERIFY2(line[1] != cell11, "Ensure cell changed");
	field->setLineOfCells(line);

	const int NUMBER_OF_CELLS_CHANGED = 1;
	QCOMPARE(spy.count(), NUMBER_OF_CELLS_CHANGED);
	QVERIFY(qvariant_cast<AddressOfCell>(spy.takeFirst().at(0)) == address11);
}

void CellsFieldModelTest::getCellsField_should_return_CellsField_with_equal_content()
{
	CellsFieldModel cellsFieldModel(6, 10);
	cellsFieldModel.setCell({{0, 1}, cellSign::SGN_DOT});
	cellsFieldModel.setCell({{0, 2}, cellSign::SGN_DOT});
	cellsFieldModel.setCell({{0, 3}, cellSign::SGN_FILL_BLACK});
	cellsFieldModel.setCell({{1, 1}, cellSign::SGN_EMPTY});
	cellsFieldModel.setCell({{1, 2}, cellSign::SGN_FILL_BLACK});
	cellsFieldModel.setCell({{1, 3}, cellSign::SGN_DOT});

	CellsField cellsField = cellsFieldModel.getCellsField();

	QCOMPARE(     cellsField.getCell({0, 1}).getSign(),
	         cellsFieldModel.getCell({0, 1}).getSign());
	QCOMPARE(     cellsField.getCell({0, 2}).getSign(),
	         cellsFieldModel.getCell({0, 2}).getSign());
	QCOMPARE(     cellsField.getCell({0, 3}).getSign(),
	         cellsFieldModel.getCell({0, 3}).getSign());
	QCOMPARE(     cellsField.getCell({1, 1}).getSign(),
	         cellsFieldModel.getCell({1, 1}).getSign());
	QCOMPARE(     cellsField.getCell({1, 2}).getSign(),
	         cellsFieldModel.getCell({1, 2}).getSign());
	QCOMPARE(     cellsField.getCell({1, 3}).getSign(),
	         cellsFieldModel.getCell({1, 3}).getSign());
	QCOMPARE(     cellsField.getCell({2, 5}).getSign(),
	         cellsFieldModel.getCell({2, 5}).getSign());
}

void CellsFieldModelTest::setCellsField_should_set_equal_content_as_in_CellsField()
{
	CellsFieldModel cellsFieldModel(6, 10);
	cellsFieldModel.setCell({{0, 1}, cellSign::SGN_DOT});
	cellsFieldModel.setCell({{0, 2}, cellSign::SGN_DOT});
	cellsFieldModel.setCell({{0, 3}, cellSign::SGN_FILL_BLACK});
	cellsFieldModel.setCell({{1, 1}, cellSign::SGN_FILL_BLACK});
	cellsFieldModel.setCell({{1, 2}, cellSign::SGN_FILL_BLACK});
	cellsFieldModel.setCell({{1, 3}, cellSign::SGN_DOT});
	// only for CellsFieldModel
	cellsFieldModel.setCell({{3, 6}, cellSign::SGN_FILL_BLACK});

	CellsField cellsField(5, 8);
	cellsField.setCell({{0, 1}, cellSign::SGN_EMPTY});
	cellsField.setCell({{0, 2}, cellSign::SGN_FILL_BLACK});
	cellsField.setCell({{0, 3}, cellSign::SGN_EMPTY});
	cellsField.setCell({{1, 1}, cellSign::SGN_DOT});
	cellsField.setCell({{1, 2}, cellSign::SGN_DOT});
	cellsField.setCell({{1, 3}, cellSign::SGN_EMPTY});
	// only for CellsField
	cellsField.setCell({{2, 5}, cellSign::SGN_FILL_BLACK});

	cellsFieldModel.setCellsField(cellsField);

	QCOMPARE(cellsFieldModel.getCell({0, 1}).getSign(),
	              cellsField.getCell({0, 1}).getSign());
	QCOMPARE(cellsFieldModel.getCell({0, 2}).getSign(),
	              cellsField.getCell({0, 2}).getSign());
	QCOMPARE(cellsFieldModel.getCell({0, 3}).getSign(),
	              cellsField.getCell({0, 3}).getSign());
	QCOMPARE(cellsFieldModel.getCell({1, 1}).getSign(),
	              cellsField.getCell({1, 1}).getSign());
	QCOMPARE(cellsFieldModel.getCell({1, 2}).getSign(),
	              cellsField.getCell({1, 2}).getSign());
	QCOMPARE(cellsFieldModel.getCell({1, 3}).getSign(),
	              cellsField.getCell({1, 3}).getSign());
	QCOMPARE(cellsFieldModel.getCell({2, 5}).getSign(),
	              cellsField.getCell({2, 5}).getSign());
	QCOMPARE(cellsFieldModel.getCell({3, 6}).getSign(),
	              cellsField.getCell({3, 6}).getSign());
}

QSharedPointer<CellsFieldModel> CellsFieldModelTest::makeEmptyCellsField()
{
	return QSharedPointer<CellsFieldModel>(new CellsFieldModel(width, height));
}

QSharedPointer<CellsFieldModel> CellsFieldModelTest::makeFilledCellsField()
{
	QSharedPointer<CellsFieldModel> field = makeEmptyCellsField();
	field->setCell(cell01);
	field->setCell(cell10);
	field->setCell(cell11);
	field->setCell(cell21);
	return field;
}
