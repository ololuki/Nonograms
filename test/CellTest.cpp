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
#include "CellTest.h"

void CellTest::x_and_y_of_Address_should_be_same_as_given_in_constructor()
{
	AddressOfCell address = AddressOfCell(3, 5);
	Cell cell = Cell(address);
	QCOMPARE(cell.getAddress().getX(), 3);
	QCOMPARE(cell.getAddress().getY(), 5);
}

void CellTest::isFilledBlack_should_return_true_only_if_sign_FillBlack_was_given_in_constructor()
{
	Cell cell = Cell(dummyAddress, cellSign::SGN_FILL_BLACK);
	QCOMPARE(cell.isFilledBlack(), true);
	
	cell = Cell(dummyAddress, cellSign::SGN_EMPTY);
	QCOMPARE(cell.isFilledBlack(), false);
	cell = Cell(dummyAddress, cellSign::SGN_FILLED);
	QCOMPARE(cell.isFilledBlack(), false);
	cell = Cell(dummyAddress, cellSign::SGN_DOT);
	QCOMPARE(cell.isFilledBlack(), false);
}

void CellTest::isDot_should_return_true_only_if_sign_Dot_was_given_in_constructor()
{
	Cell cell = Cell(dummyAddress, cellSign::SGN_DOT);
	QCOMPARE(cell.isDot(), true);
	
	cell = Cell(dummyAddress, cellSign::SGN_EMPTY);
	QCOMPARE(cell.isDot(), false);
	cell = Cell(dummyAddress, cellSign::SGN_FILLED);
	QCOMPARE(cell.isDot(), false);
	cell = Cell(dummyAddress, cellSign::SGN_FILL_BLACK);
	QCOMPARE(cell.isDot(), false);
}

void CellTest::isEmpty_should_return_true_only_if_sign_Empty_was_given_in_constructor()
{
	Cell cell = Cell(dummyAddress, cellSign::SGN_EMPTY);
	QCOMPARE(cell.isEmpty(), true);
	
	cell = Cell(dummyAddress, cellSign::SGN_FILLED);
	QCOMPARE(cell.isEmpty(), false);
	cell = Cell(dummyAddress, cellSign::SGN_DOT);
	QCOMPARE(cell.isEmpty(), false);
	cell = Cell(dummyAddress, cellSign::SGN_FILL_BLACK);
	QCOMPARE(cell.isEmpty(), false);
}

void CellTest::default_sign_should_be_empty_for_Address_in_constructor()
{
	Cell cell = Cell(dummyAddress);
	QCOMPARE(cell.isEmpty(), true);
	QCOMPARE(cell.isDot(), false);
	QCOMPARE(cell.isFilledBlack(), false);
}

void CellTest::default_sign_should_be_empty_for_default_constructor()
{
	Cell cell = Cell();
	QCOMPARE(cell.isEmpty(), true);
	QCOMPARE(cell.isDot(), false);
	QCOMPARE(cell.isFilledBlack(), false);
}

void CellTest::cells_are_equal_if_have_same_signs()
{
	Cell cellA = Cell(dummyAddress, cellSign::SGN_DOT);
	Cell cellB = Cell(dummyAddress, cellSign::SGN_DOT);
	QVERIFY(cellA == cellB);
	QCOMPARE(cellA != cellB, false);
}

void CellTest::cells_are_equal_if_have_same_signs_and_different_addresses()
{
	Cell cellA = Cell(AddressOfCell(1, 2), cellSign::SGN_DOT);
	Cell cellB = Cell(AddressOfCell(18, 34), cellSign::SGN_DOT);
	QVERIFY(cellA == cellB);
	QCOMPARE(cellA != cellB, false);
}

void CellTest::cells_are_not_equal_if_have_different_signs()
{
	Cell cellA = Cell(dummyAddress, cellSign::SGN_EMPTY);
	Cell cellB = Cell(dummyAddress, cellSign::SGN_FILL_BLACK);
	QVERIFY(cellA != cellB);
	QCOMPARE(cellA == cellB, false);
}
