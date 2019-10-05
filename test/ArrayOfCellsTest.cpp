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
#include "ArrayOfCellsTest.h"


void ArrayOfCellsTest::operator_parentheses_x_y_should_return_reference_to_Cell()
{
	ArrayOfCells array(2, 3);
	array(0, 0).makeEmpty();
	QCOMPARE(array(0, 0).isDot(), false);
	array(0, 0).makeDot();
	QCOMPARE(array(0, 0).isDot(), true);
}

void ArrayOfCellsTest::operator_parentheses_x_y_should_return_Cell_with_suitable_Address()
{
	ArrayOfCells array(2, 2);
	QVERIFY( array(0, 0).getAddress() == AddressOfCell(0, 0) );
	QVERIFY( array(0, 1).getAddress() == AddressOfCell(0, 1) );
	QVERIFY( array(1, 0).getAddress() == AddressOfCell(1, 0) );
}

void ArrayOfCellsTest::order_of_ctor_args_should_be_same_as_order_of_operator_parentheses_x_y()
{
	ArrayOfCells array(3, 14);
	QVERIFY( array(2, 13).getAddress() == AddressOfCell(2, 13) );
}

void ArrayOfCellsTest::width_and_height_should_return_width_and_height_of_array()
{
	ArrayOfCells array(3, 14);
	QCOMPARE( array.width(), 3 );
	QCOMPARE( array.height(), 14 );
}

void ArrayOfCellsTest::width_and_height_for_empty_array_should_return_0_and_0()
{
	ArrayOfCells emptyArray(0, 0);
	QCOMPARE( emptyArray.width(), 0 );
	QCOMPARE( emptyArray.height(), 0 );
}

void ArrayOfCellsTest::areSolvedCellsEqual_returns_true_for_empty_arrays_same_size()
{
	ArrayOfCells arrayA(3, 14);
	ArrayOfCells arrayB(3, 14);
	QCOMPARE(arrayA.areSolvedCellsEqual(arrayB), true);
}

/// just test if there are not accessing to elements in empty vectors
void ArrayOfCellsTest::areSolvedCellsEqual_returns_true_for_arrays_zero_size()
{
	ArrayOfCells arrayA(0, 0);
	ArrayOfCells arrayB(0, 0);
	QCOMPARE(arrayA.areSolvedCellsEqual(arrayB), true);
}

void ArrayOfCellsTest::areSolvedCellsEqual_returns_false_for_empty_arrays_different_size()
{
	ArrayOfCells arrayA(3, 14);
	ArrayOfCells arrayB(2, 5);
	QCOMPARE(arrayA.areSolvedCellsEqual(arrayB), false);
}

/// if both arrays have solved (filled or dot) cells in same places
/// then they are equal
/// empty cells does not matter
/// if one array have solved cell and other has empty (not resolved)
/// then it does not affect the result
void ArrayOfCellsTest::areSolvedCellsEqual_returns_true_for_arrays_with_some_solved_cells()
{
	ArrayOfCells arrayA(3, 14);
	ArrayOfCells arrayB(3, 14);

	// same solved in both
	arrayA(0, 0).makeFilledBlack();
	arrayB(0, 0).makeFilledBlack();

	arrayA(2, 7).makeFilledBlack();
	arrayB(2, 7).makeFilledBlack();

	arrayA(2, 13).makeDot();
	arrayB(2, 13).makeDot();

	// set solved only in one array - should not be taken into account
	arrayA(1, 1).makeFilledBlack();
	arrayA(1, 3).makeDot();

	arrayB(2, 2).makeFilledBlack();
	arrayB(2, 4).makeDot();

	QCOMPARE(arrayA.areSolvedCellsEqual(arrayB), true);
}

/// if cell in one array is solved different than in other on same address
/// (for example filled and dot)
/// then arrays are not equal
void ArrayOfCellsTest::areSolvedCellsEqual_returns_false_for_arrays_with_cells_solved_differentially()
{
	ArrayOfCells arrayA(3, 14);
	ArrayOfCells arrayB(3, 14);

	// same solved in both
	arrayA(0, 0).makeFilledBlack();
	arrayB(0, 0).makeFilledBlack();

	// different in both
	arrayA(2, 2).makeFilledBlack();
	arrayB(2, 2).makeDot();

	QCOMPARE(arrayA.areSolvedCellsEqual(arrayB), false);
}
