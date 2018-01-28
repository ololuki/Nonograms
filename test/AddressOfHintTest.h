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
#ifndef ADDRESSOFHINTTEST_H
#define ADDRESSOFHINTTEST_H

#include <QtTest>
#include "field/AddressOfHint.h"


class AddressOfHintTest : public QObject
{
	Q_OBJECT
private slots:
	void orientation_line_and_count_of_Address_should_be_same_as_given_in_constructor();
	void default_constructor_makes_invalid_Address();
	void Address_is_invalid_for_negative_line_or_count();
	void Address_compared_with_itself_is_equal();
	void Addresses_with_same_x_and_y_are_equal();
	void Addresses_with_different_x_are_NOT_equal();
	void Addresses_with_different_y_are_NOT_equal();
	void Addresses_with_different_orientation_are_NOT_equal();
	void isColumn_returns_true_only_for_vertical_orientation();
	void isRow_returns_true_only_for_horizontal_orientation();
};

#endif // ADDRESSOFHINTTEST_H
