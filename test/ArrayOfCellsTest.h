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
#ifndef ARRAYOFCELLSTEST_H
#define ARRAYOFCELLSTEST_H

#include <QtTest>
#include "field/ArrayOfCells.h"


class ArrayOfCellsTest : public QObject
{
	Q_OBJECT
private slots:
	void operator_parentheses_x_y_should_return_reference_to_Cell();
	void operator_parentheses_x_y_should_return_Cell_with_suitable_Address();
	void order_of_ctor_args_should_be_same_as_order_of_operator_parentheses_x_y(); //eg. array(x, y) <=> ArrayOfCells(x, y)
	void width_and_height_should_return_width_and_height_of_array();
	void width_and_height_for_empty_array_should_return_0_and_0();
};

#endif // ARRAYOFCELLSTEST_H
