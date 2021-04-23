/**********************************************************************
 * Copyright (C) 2017 - 2018 Ololuki
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
#include "AddressOfHintTest.h"


void AddressOfHintTest::orientation_line_and_count_of_Address_should_be_same_as_given_in_constructor()
{
	int line = 2;
	int count = 3;
	Orientation o = Orientation::VERTICAL;
	AddressOfHint address(o, line, count);
	QVERIFY(address.getLine() == line);
	QVERIFY(address.getCount() == count);
	QVERIFY(address.getOrientation() == o);
}

void AddressOfHintTest::default_constructor_makes_invalid_Address()
{
	AddressOfHint address{};
	QCOMPARE(address.isValid(), false);
}

void AddressOfHintTest::Address_is_invalid_for_negative_line_or_count()
{
	QCOMPARE(AddressOfHint(Orientation::HORIZONTAL, 3, -1).isValid(), false);
	QCOMPARE(AddressOfHint(Orientation::HORIZONTAL, -5, -6).isValid(), false);
	QCOMPARE(AddressOfHint(Orientation::HORIZONTAL, -1, 2).isValid(), false);
	
	QCOMPARE(AddressOfHint(Orientation::HORIZONTAL, 0, 0).isValid(), true);
	QCOMPARE(AddressOfHint(Orientation::HORIZONTAL, 6, 5).isValid(), true);
	QCOMPARE(AddressOfHint(Orientation::HORIZONTAL, 0, 5).isValid(), true);
	QCOMPARE(AddressOfHint(Orientation::HORIZONTAL, 6, 0).isValid(), true);
}

void AddressOfHintTest::Address_compared_with_itself_is_equal()
{
	AddressOfHint address(Orientation::VERTICAL, 1, 2);
	QVERIFY(address == address);
	QCOMPARE((address != address), false);
}

void AddressOfHintTest::Addresses_with_same_x_and_y_are_equal()
{
	AddressOfHint addressA(Orientation::VERTICAL, 2, 6);
	AddressOfHint addressB(Orientation::VERTICAL, 2, 6);
	QVERIFY(addressA == addressB);
	QCOMPARE((addressA != addressB), false);
}

void AddressOfHintTest::Addresses_with_different_x_are_NOT_equal()
{
	AddressOfHint addressA(Orientation::VERTICAL, 1, 6);
	AddressOfHint addressB(Orientation::VERTICAL, 2, 6);
	QVERIFY(addressA != addressB);
	QCOMPARE((addressA == addressB), false);
}

void AddressOfHintTest::Addresses_with_different_y_are_NOT_equal()
{
	AddressOfHint addressA(Orientation::VERTICAL, 2, 5);
	AddressOfHint addressB(Orientation::VERTICAL, 2, 6);
	QVERIFY(addressA != addressB);
	QCOMPARE((addressA == addressB), false);
}

void AddressOfHintTest::Addresses_with_different_orientation_are_NOT_equal()
{
	AddressOfHint addressA(Orientation::HORIZONTAL, 2, 6);
	AddressOfHint addressB(Orientation::VERTICAL, 2, 6);
	QVERIFY(addressA != addressB);
	QCOMPARE((addressA == addressB), false);
}

void AddressOfHintTest::isColumn_returns_true_only_for_vertical_orientation()
{
	AddressOfHint addressA(Orientation::VERTICAL, 2, 6);
	QCOMPARE(addressA.isColumn(), true);
	AddressOfHint addressB(Orientation::HORIZONTAL, 2, 6);
	QCOMPARE(addressB.isColumn(), false);
}

void AddressOfHintTest::isRow_returns_true_only_for_horizontal_orientation()
{
	AddressOfHint addressA(Orientation::HORIZONTAL, 2, 6);
	QCOMPARE(addressA.isRow(), true);
	AddressOfHint addressB(Orientation::VERTICAL, 2, 6);
	QCOMPARE(addressB.isRow(), false);
}
