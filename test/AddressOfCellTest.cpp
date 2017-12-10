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
#include "AddressOfCellTest.h"


void AddressOfCellTest::x_and_y_of_Address_should_be_same_as_given_in_constructor()
{
	AddressOfCell address(0, 2);
	QCOMPARE( address.getX(), 0 );
	QCOMPARE( address.getY(), 2 );
}

void AddressOfCellTest::Address_compared_with_itself_is_equal()
{
	AddressOfCell address(1, 2);
	QVERIFY( address == address );
}

void AddressOfCellTest::Addresses_with_same_x_and_y_are_equal()
{
	AddressOfCell addressA(1, 3);
	AddressOfCell addressB(1, 3);
	QVERIFY( addressA == addressB );
}

void AddressOfCellTest::Addresses_with_different_x_and_y_are_NOT_equal()
{
	AddressOfCell addressA(0, 2);
	AddressOfCell addressB(1, 3);
	QCOMPARE( (addressA == addressB), false );
	QVERIFY( addressA != addressB );
	unsigned int a = 1;
	QCOMPARE( (AddressOfCell(a, a) == AddressOfCell(a, a+1)), false );
	QCOMPARE( (AddressOfCell(a, a) == AddressOfCell(a+1, a)), false );
	QVERIFY( AddressOfCell(a, a) != AddressOfCell(a, a+1) );
	QVERIFY( AddressOfCell(a, a) != AddressOfCell(a+1, a) );
}

void AddressOfCellTest::max_x_and_y_should_be_at_least_10000()
{
	AddressOfCell address(10000, 10000);
	QCOMPARE(address.getX(), 10000);
	QCOMPARE(address.getY(), 10000);
}
