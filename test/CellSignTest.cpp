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
#include "CellSignTest.h"


Q_DECLARE_METATYPE(cellSign)

void CellSignTest::utils_from_char_and_to_char_conversion_test_data()
{
	QTest::addColumn<cellSign>("d_cellSign");
	QTest::addColumn<char>("d_char");
	
	QTest::newRow("empty")      << cellSign::SGN_EMPTY      << '-';
	QTest::newRow("dot")        << cellSign::SGN_DOT        << '.';
	QTest::newRow("fill black") << cellSign::SGN_FILL_BLACK << '#';
}

void CellSignTest::utils_from_char_and_to_char_conversion_test()
{
	QFETCH(cellSign, d_cellSign);
	QFETCH(char, d_char);
	
	QCOMPARE(CellSignUtils::fromChar(d_char), d_cellSign);
	QCOMPARE(CellSignUtils::toChar(d_cellSign), d_char);
}
