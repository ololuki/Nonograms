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
#include "CellsFieldTest.h"
#include "field/CellsField.h"

Q_DECLARE_METATYPE(CellsField)


/// Test valid initializer list with rows
/// All rows must have same length
void CellsFieldTest::constructor_initializer_list()
{
	CellsField cellsField{
		LineOfCells("--#.-"),
		LineOfCells("#-#.#"),
		LineOfCells("--#..")
	};

	QCOMPARE(cellsField.getWidth(), 5);
	QCOMPARE(cellsField.getHeight(), 3);
	QVERIFY(cellsField.getCell({0, 0}) == CellSignUtils::fromChar('-'));
	QVERIFY(cellsField.getCell({1, 0}) == CellSignUtils::fromChar('-'));
	QVERIFY(cellsField.getCell({2, 0}) == CellSignUtils::fromChar('#'));
	QVERIFY(cellsField.getCell({3, 0}) == CellSignUtils::fromChar('.'));
	QVERIFY(cellsField.getCell({4, 0}) == CellSignUtils::fromChar('-'));

	QVERIFY(cellsField.getCell({0, 1}) == CellSignUtils::fromChar('#'));
	QVERIFY(cellsField.getCell({1, 1}) == CellSignUtils::fromChar('-'));
	QVERIFY(cellsField.getCell({2, 1}) == CellSignUtils::fromChar('#'));
	QVERIFY(cellsField.getCell({3, 1}) == CellSignUtils::fromChar('.'));
	QVERIFY(cellsField.getCell({4, 1}) == CellSignUtils::fromChar('#'));

	QVERIFY(cellsField.getCell({0, 2}) == CellSignUtils::fromChar('-'));
	QVERIFY(cellsField.getCell({1, 2}) == CellSignUtils::fromChar('-'));
	QVERIFY(cellsField.getCell({2, 2}) == CellSignUtils::fromChar('#'));
	QVERIFY(cellsField.getCell({3, 2}) == CellSignUtils::fromChar('.'));
	QVERIFY(cellsField.getCell({4, 2}) == CellSignUtils::fromChar('.'));
}

/// Passing not valid list (with lines with different legths)
/// should make empty CellsField
void CellsFieldTest::constructor_initializer_list_not_valid_make_empty()
{
	// add longer and shorter line than first
	CellsField cellsField{
		LineOfCells("--#.-"),
		LineOfCells("#-#.#--"),
		LineOfCells("#")
	};

	QCOMPARE(cellsField.getWidth(), 0);
	QCOMPARE(cellsField.getHeight(), 0);
}

/// Empty initializer list should make empty CellsField
void CellsFieldTest::constructor_initializer_list_empty_list_make_empty()
{
	CellsField cellsField{};

	QCOMPARE(cellsField.getWidth(), 0);
	QCOMPARE(cellsField.getHeight(), 0);
}

void CellsFieldTest::equality_opeators_compare_cell_sign_equal_data()
{
	QTest::addColumn<CellsField>("d_fieldA");
	QTest::addColumn<CellsField>("d_fieldB");

	QTest::newRow("empty") << CellsField() << CellsField();

	QTest::newRow("1x1") << CellsField{
	                        LineOfCells("#")}
	                     << CellsField{
	                        LineOfCells("#")};

	QTest::newRow("5x3") << CellsField{
	                        LineOfCells("--#.-"),
	                        LineOfCells("#-#.#"),
	                        LineOfCells("#----")}
	                     << CellsField{
	                        LineOfCells("--#.-"),
	                        LineOfCells("#-#.#"),
	                        LineOfCells("#----")};
}

void CellsFieldTest::equality_opeators_compare_cell_sign_equal()
{
	QFETCH(CellsField, d_fieldA);
	QFETCH(CellsField, d_fieldB);

	QVERIFY(d_fieldA == d_fieldB);
	QCOMPARE(d_fieldA, d_fieldB);
	QCOMPARE(d_fieldA != d_fieldB, false);
}

void CellsFieldTest::equality_opeators_compare_cell_sign_not_equal_data()
{
	QTest::addColumn<CellsField>("d_fieldA");
	QTest::addColumn<CellsField>("d_fieldB");

	QTest::newRow("1x1") << CellsField{
	                        LineOfCells("-")}
	                     << CellsField{
	                        LineOfCells("#")};

	QTest::newRow("5x3") << CellsField{
	                        LineOfCells("-----"),
	                        LineOfCells("-----"),
	                        LineOfCells("-----")}
	                     << CellsField{
	                        LineOfCells("-----"),
	                        LineOfCells("-----"),
	                        LineOfCells("----.")};

	QTest::newRow("5x3") << CellsField{
	                        LineOfCells("-----"),
	                        LineOfCells("-----"),
	                        LineOfCells("-----")}
	                     << CellsField{
	                        LineOfCells("-----"),
	                        LineOfCells("-----"),
	                        LineOfCells("----#")};

	QTest::newRow("different number of lines")
	        << CellsField{
	           LineOfCells("-----"),
	           LineOfCells("-----"),
	           LineOfCells("-----")}
	        << CellsField{
	           LineOfCells("-----"),
	           LineOfCells("-----")};

	CellsField someCellsField{
		LineOfCells("....#"),
		LineOfCells("....#"),
		LineOfCells("....#")};
	CellsField copiedCellsField(someCellsField);
	copiedCellsField.setCell(Cell(AddressOfCell(0, 0), cellSign::SGN_EMPTY));
	QTest::newRow("copy and modify") << someCellsField << copiedCellsField;
}

void CellsFieldTest::equality_opeators_compare_cell_sign_not_equal()
{
	QFETCH(CellsField, d_fieldA);
	QFETCH(CellsField, d_fieldB);

	QCOMPARE(d_fieldA == d_fieldB, false);
	QVERIFY(d_fieldA != d_fieldB);
}
