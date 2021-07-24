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
#include "HintTest.h"


void HintTest::default_hint_should_be_filled_black_for_block_size_only_param_in_constructor()
{
	Hint hint = Hint(2);
	QCOMPARE(hint.isFilledBlack(), true);
}

void HintTest::default_hint_should_be_filled_black_for_Address_in_constructor()
{
	AddressOfHint dummyAddress = AddressOfHint(Orientation::VERTICAL, 3, 5);
	Hint hint = Hint(dummyAddress, 2);
	QCOMPARE(hint.isFilledBlack(), true);
}

void HintTest::getBlockSize_should_return_size_given_in_constructor()
{
	Hint hint = Hint(23);
	QCOMPARE(hint.getBlockSize(), 23);
}

void HintTest::getBlockSize_should_return_size_given_in_setBlockSize()
{
	Hint hint = Hint(1);
	hint.setBlockSize(236);
	QCOMPARE(hint.getBlockSize(), 236);
}

void HintTest::isFilledBlack_should_be_true_for_cell_sign_fill_black_given_in_constructor()
{
	Hint hint = Hint(1, cellSign::SGN_FILL_BLACK);
	QCOMPARE(hint.isFilledBlack(), true);
}

void HintTest::isFilledBlack_should_be_true_after_make_fill_black()
{
	Hint hint = Hint(1, cellSign::SGN_EMPTY);
	hint.makeFilledBlack();
	QCOMPARE(hint.isFilledBlack(), true);
}

void HintTest::isFilledBlack_should_be_true_for_char_filled_black_given_in_constructor()
{
	Hint hint = Hint(1, CellSignUtils::toChar(cellSign::SGN_FILL_BLACK));
	QCOMPARE(hint.isFilledBlack(), true);
}

void HintTest::isFilledBlack_should_be_false_for_other_cell_sign_given_in_constructor()
{
	Hint hint = Hint(1, cellSign::SGN_EMPTY);
	QCOMPARE(hint.isFilledBlack(), false);
}

void HintTest::isFilledBlack_should_be_false_for_other_char_given_in_constructor()
{
	Hint hint = Hint(1, CellSignUtils::toChar(cellSign::SGN_EMPTY));
	QCOMPARE(hint.isFilledBlack(), false);
}

void HintTest::address_should_be_invalid_for_constructors_without_address()
{
	Hint hint = Hint(4);
	QCOMPARE(hint.getAddress().isValid(), false);
}

void HintTest::getAddress_should_give_same_address_as_given_in_constructor()
{
	AddressOfHint address = AddressOfHint(Orientation::VERTICAL, 3, 5);
	Hint hint = Hint(address, 2);
	QVERIFY(hint.getAddress() == address);
}

void HintTest::equality_operators_equal_for_same_blockSize_and_CellSign()
{
	Hint hintA = Hint(15, cellSign::SGN_FILL_BLACK);
	Hint hintB = Hint(15, cellSign::SGN_FILL_BLACK);

	QCOMPARE(hintA, hintB);
	QVERIFY(hintA == hintB);
	QCOMPARE(hintA != hintB, false);
}

void HintTest::equality_operators_not_equal_for_different_blockSize()
{
	Hint hintA = Hint(15, cellSign::SGN_FILL_BLACK);
	Hint hintB = Hint(20, cellSign::SGN_FILL_BLACK);

	QVERIFY(hintA != hintB);
	QCOMPARE(hintA == hintB, false);
}

void HintTest::equality_operators_not_equal_for_different_CellSign()
{
	Hint hintA = Hint(2, cellSign::SGN_FILL_BLACK);
	Hint hintB = Hint(2, cellSign::SGN_FILLED);

	QVERIFY(hintA != hintB);
	QCOMPARE(hintA == hintB, false);
}
