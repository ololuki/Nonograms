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
#include "LineOfCellsTest.h"
#include "utils/NVector.h"


void LineOfCellsTest::size_should_return_size()
{
	LineOfCells lineOfCells(NVector<Cell>(3, Cell(dummyAddress)));
	QCOMPARE(lineOfCells.size(), 3);
}

void LineOfCellsTest::implicit_Cells_should_be_empty()
{
	LineOfCells lineOfCells(NVector<Cell>(2, Cell(dummyAddress)));
	QCOMPARE(lineOfCells[0].isEmpty(), true);
	QCOMPARE(lineOfCells[1].isEmpty(), true);
}

void LineOfCellsTest::operator_square_brackets_should_return_reference_to_Cell()
{
	LineOfCells lineOfCells(NVector<Cell>(2, Cell(dummyAddress)));
	QCOMPARE(lineOfCells[0].isDot(), false);
	lineOfCells[0].makeDot();
	QCOMPARE(lineOfCells[0].isDot(), true);
}

void LineOfCellsTest::at_should_return_reference_to_Cell()
{
	LineOfCells lineOfCells(NVector<Cell>(2, Cell(dummyAddress)));
	QCOMPARE(lineOfCells.at(0).isDot(), false);
	lineOfCells.at(0).makeDot();
	QCOMPARE(lineOfCells.at(0).isDot(), true);
}

void LineOfCellsTest::max_size_should_be_at_least_10000()
{
	LineOfCells lineOfCells(NVector<Cell>(10000, Cell(dummyAddress)));
	QCOMPARE(lineOfCells.size(), 10000);
}

/// Check only for valid address values passed to c-tor, do not check for invalid
void LineOfCellsTest::addresses_passed_in_constructor_stay_unchanged_check_for_x()
{
	NVector<Cell> cellVector;
	cellVector.push_back(Cell(AddressOfCell(0, 0)));
	cellVector.push_back(Cell(AddressOfCell(1, 0)));
	cellVector.push_back(Cell(AddressOfCell(2, 0)));
	LineOfCells lineOfCells(cellVector);
	QCOMPARE(lineOfCells.at(0).getAddress().getX(), 0);
	QCOMPARE(lineOfCells.at(1).getAddress().getX(), 1);
	QCOMPARE(lineOfCells.at(2).getAddress().getX(), 2);
}

/// Check only for valid address values passed to c-tor, do not check for invalid
void LineOfCellsTest::addresses_passed_in_constructor_stay_unchanged_check_for_y()
{
	NVector<Cell> cellVector;
	cellVector.push_back(Cell(AddressOfCell(0, 0)));
	cellVector.push_back(Cell(AddressOfCell(0, 1)));
	cellVector.push_back(Cell(AddressOfCell(0, 2)));
	LineOfCells lineOfCells(cellVector);
	QCOMPARE(lineOfCells.at(0).getAddress().getY(), 0);
	QCOMPARE(lineOfCells.at(1).getAddress().getY(), 1);
	QCOMPARE(lineOfCells.at(2).getAddress().getY(), 2);
}

void LineOfCellsTest::address_should_stay_unchanged_after_makeFilledBlack_makeDot_and_makeEmpty()
{
	NVector<Cell> cellVector;
	cellVector.push_back(Cell(AddressOfCell(0, 0)));
	LineOfCells lineOfCells(cellVector);
	
	lineOfCells.at(0).makeFilledBlack();
	QVERIFY(lineOfCells.at(0).getAddress() == AddressOfCell(0, 0));
	lineOfCells.at(0).makeDot();
	QVERIFY(lineOfCells.at(0).getAddress() == AddressOfCell(0, 0));
	lineOfCells.at(0).makeEmpty();
	QVERIFY(lineOfCells.at(0).getAddress() == AddressOfCell(0, 0));
}

void LineOfCellsTest::Cells_are_filled_black_after_setting_them()
{
	NVector<Cell> cellVector;
	cellVector.push_back(Cell(AddressOfCell(0, 0)));
	LineOfCells lineOfCells(cellVector);
	lineOfCells.at(0).makeFilledBlack();
	QCOMPARE(lineOfCells.at(0).isFilledBlack(), true);
}

void LineOfCellsTest::Cells_are_dot_after_setting_them()
{
	NVector<Cell> cellVector;
	cellVector.push_back(Cell(AddressOfCell(0, 0)));
	LineOfCells lineOfCells(cellVector);
	lineOfCells[0].makeDot();
	QCOMPARE(lineOfCells[0].isDot(), true);
}

void LineOfCellsTest::constructor_from_string_test()
{
	LineOfCells lineOfCells = LineOfCells("--#.-");
	QCOMPARE(lineOfCells.size(), 5);
	QVERIFY(lineOfCells.at(0) == CellSignUtils::fromChar('-'));
	QVERIFY(lineOfCells.at(1) == CellSignUtils::fromChar('-'));
	QVERIFY(lineOfCells.at(2) == CellSignUtils::fromChar('#'));
	QVERIFY(lineOfCells.at(3) == CellSignUtils::fromChar('.'));
	QVERIFY(lineOfCells.at(4) == CellSignUtils::fromChar('-'));
}

void LineOfCellsTest::constructor_from_empty_string_makes_zero_length_line()
{
	LineOfCells lineOfCells = LineOfCells("");
	QCOMPARE(lineOfCells.size(), 0);
}

void LineOfCellsTest::equality_opeators_compare_cell_sign_equal_data()
{
	QTest::addColumn<LineOfCells>("d_lineA");
	QTest::addColumn<LineOfCells>("d_lineB");

	QTest::newRow("empty")    << LineOfCells{""}      << LineOfCells{""};
	QTest::newRow("one char") << LineOfCells{"-"}     << LineOfCells{"-"};
	QTest::newRow("one char") << LineOfCells{"."}     << LineOfCells{"."};
	QTest::newRow("one char") << LineOfCells{"#"}     << LineOfCells{"#"};
	QTest::newRow("longer")   << LineOfCells{"#####"} << LineOfCells{"#####"};
	QTest::newRow("mixed")    << LineOfCells{"--#.-"} << LineOfCells{"--#.-"};
	QTest::newRow("mixed")    << LineOfCells{"###-"}  << LineOfCells{"###-"};
	QTest::newRow("mixed")    << LineOfCells{".#"}    << LineOfCells{".#"};
}

void LineOfCellsTest::equality_opeators_compare_cell_sign_equal()
{
	QFETCH(LineOfCells, d_lineA);
	QFETCH(LineOfCells, d_lineB);

	QVERIFY(d_lineA == d_lineB);
	QCOMPARE(d_lineA, d_lineB);
	QCOMPARE(d_lineA != d_lineB, false);
}

void LineOfCellsTest::equality_opeators_compare_cell_sign_not_equal_data()
{
	QTest::addColumn<LineOfCells>("d_lineA");
	QTest::addColumn<LineOfCells>("d_lineB");

	QTest::newRow("one char")  << LineOfCells{"-"}     << LineOfCells{"."};
	QTest::newRow("one char")  << LineOfCells{"."}     << LineOfCells{"#"};
	QTest::newRow("one char")  << LineOfCells{"#"}     << LineOfCells{"-"};
	QTest::newRow("diff size") << LineOfCells{"#####"} << LineOfCells{"######"};
	QTest::newRow("diff size") << LineOfCells{"####"}  << LineOfCells{"#####"};
	QTest::newRow("mixed")     << LineOfCells{".-#.-"} << LineOfCells{"--#.-"};
	QTest::newRow("mixed")     << LineOfCells{"--#.."} << LineOfCells{"--#.-"};
}

void LineOfCellsTest::equality_opeators_compare_cell_sign_not_equal()
{
	QFETCH(LineOfCells, d_lineA);
	QFETCH(LineOfCells, d_lineB);

	QCOMPARE((d_lineA == d_lineB), false);
	QVERIFY(d_lineA != d_lineB);
}
