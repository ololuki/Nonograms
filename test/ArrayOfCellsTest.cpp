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
