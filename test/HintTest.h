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
#ifndef HINTTEST_H
#define HINTTEST_H

#include <QtTest>
#include "field/Hint.h"


class HintTest : public QObject
{
	Q_OBJECT
private slots:
	void default_hint_should_be_filled_black_for_block_size_only_param_in_constructor();
	void default_hint_should_be_filled_black_for_Address_in_constructor();
	
	void getBlockSize_should_return_size_given_in_constructor();
	void getBlockSize_should_return_size_given_in_setBlockSize();
	
	void isFilledBlack_should_be_true_for_cell_sign_fill_black_given_in_constructor();
	void isFilledBlack_should_be_true_after_make_fill_black();
	void isFilledBlack_should_be_true_for_char_filled_black_given_in_constructor();
	void isFilledBlack_should_be_false_for_other_cell_sign_given_in_constructor();
	void isFilledBlack_should_be_false_for_other_char_given_in_constructor();
	
	void address_should_be_invalid_for_constructors_without_address();
	void getAddress_should_give_same_address_as_given_in_constructor();

	void equality_operators_equal_for_same_blockSize_and_CellSign();
	void equality_operators_not_equal_for_different_blockSize();
	void equality_operators_not_equal_for_different_CellSign();
};

#endif // HINTTEST_H
