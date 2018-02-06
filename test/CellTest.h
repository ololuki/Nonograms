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
#ifndef CELLTEST_H
#define CELLTEST_H

#include <QtTest>
#include "field/Cell.h"


class CellTest : public QObject
{
	Q_OBJECT
private slots:
	void x_and_y_of_Address_should_be_same_as_given_in_constructor();
	void address_should_be_invalid_for_default_constructor();
	void isFilledBlack_should_return_true_only_if_sign_FillBlack_was_given_in_constructor();
	void isDot_should_return_true_only_if_sign_Dot_was_given_in_constructor();
	void isEmpty_should_return_true_only_if_sign_Empty_was_given_in_constructor();
	void getSign_should_return_sign_same_as_given_in_constructor();
	void getSign_should_return_sign_same_as_given_in_constructor_with_char_param();
	void default_sign_should_be_empty_for_Address_in_constructor();
	void default_sign_should_be_empty_for_default_constructor();
	void cells_are_equal_if_have_same_signs();
	void cells_are_equal_if_have_same_signs_and_different_addresses();
	void cells_are_not_equal_if_have_different_signs();
private:
	AddressOfCell dummyAddress{0, 0};
};

#endif // CELLTEST_H
