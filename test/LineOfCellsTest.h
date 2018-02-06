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
#ifndef LINEOFCELLSTEST_H
#define LINEOFCELLSTEST_H

#include <QtTest>
#include "field/LineOfCells.h"


class LineOfCellsTest : public QObject
{
	Q_OBJECT
private slots:
	void size_should_return_size();
	void implicit_Cells_should_be_empty();
	void operator_square_brackets_should_return_reference_to_Cell();
	void at_should_return_reference_to_Cell();
	void max_size_should_be_at_least_10000();
	void addresses_passed_in_constructor_stay_unchanged_check_for_x();
	void addresses_passed_in_constructor_stay_unchanged_check_for_y();
	void address_should_stay_unchanged_after_makeFilledBlack_makeDot_and_makeEmpty();
	void Cells_are_filled_black_after_setting_them();
	void Cells_are_dot_after_setting_them();
private:
	AddressOfCell dummyAddress{0, 0};
};

#endif // LINEOFCELLSTEST_H
