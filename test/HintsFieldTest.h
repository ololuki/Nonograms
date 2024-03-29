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
#ifndef HINTSFIELDTEST_H
#define HINTSFIELDTEST_H

#include <QtTest>
#include "field/HintsField.h"


class HintsFieldTest : public QObject
{
	Q_OBJECT
private slots:
	void constructor_initializer_list_horizontal();
	void constructor_initializer_list_vertical();
	void constructor_initializer_list_empty_list_make_empty();

	void equality_opeators_compare_cell_sign_equal_data();
	void equality_opeators_compare_cell_sign_equal();
	void equality_opeators_compare_cell_sign_not_equal_data();
	void equality_opeators_compare_cell_sign_not_equal();

	void default_value_of_hint_is_zero();
	void number_of_lines_should_increase_after_insert();
	void adresses_after_insert_should_be_same_as_count_in_line();
	void value_after_insert_should_be_shifted_properly();
	void number_of_lines_should_not_change_after_update();
	void address_should_not_change_after_update();
	void block_size_value_should_change_after_update();
	void number_of_hints_in_line_should_decrease_after_delete();
	void adresses_after_delete_should_be_same_as_count_in_line();
	void hint_can_NOT_be_deleted_if_there_is_only_one_left();
	void values_after_delete_should_be_shifted_properly();

	void getLineOfHints_should_return_valid_line();
	void setLineOfHints_should_change_hints();
private:
	const Orientation orientation = Orientation::VERTICAL;
	const int numberOfLines = 2;
	const int lineNumber = 1;
	const int blockValueDefault = 0;
	const int blockValueAtZero = 5;
	const int blockValueAtFirst = 10;
	const int anotherBlockValue = 22;
	const AddressOfHint addressZero = {orientation, lineNumber, 0};
	const AddressOfHint addressFirst = {orientation, lineNumber, 1};
	const AddressOfHint addressSecond = {orientation, lineNumber, 2};
	const AddressOfHint addressThird = {orientation, lineNumber, 3};
	const Hint hintAtZero = {addressZero, blockValueAtZero};
	const Hint hintAtFirst = {addressFirst, blockValueAtFirst};
};

#endif // HINTSFIELDTEST_H
