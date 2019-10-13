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
#include "CellsFieldTest.h"
#include "field/CellsField.h"


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
