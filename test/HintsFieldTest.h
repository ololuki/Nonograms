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
#ifndef HINTSFIELDTEST_H
#define HINTSFIELDTEST_H

#include <QtTest>
#include "field/HintsField.h"


class HintsFieldTest : public QObject
{
	Q_OBJECT
private slots:
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
private:
	int numberOfLines = 2;
	int lineNumber = 1;
	int blockValueDefault = 0;
	int blockValueAtZero = 5;
	int blockValueAtFirst = 10;
	AddressOfHint addressZero = AddressOfHint(AddressOfHint::VERTICAL, lineNumber, 0);
	AddressOfHint addressFirst = AddressOfHint(AddressOfHint::VERTICAL, lineNumber, 1);
	AddressOfHint addressSecond = AddressOfHint(AddressOfHint::VERTICAL, lineNumber, 2);
	AddressOfHint addressThird = AddressOfHint(AddressOfHint::VERTICAL, lineNumber, 3);
	Hint hintAtZero = Hint(addressZero, blockValueAtZero);
	Hint hintAtFirst = Hint(addressFirst, blockValueAtFirst);
};

#endif // HINTSFIELDTEST_H
