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
#include <QtTest>
#include "AddressOfCellTest.h"
#include "AddressOfHintTest.h"
#include "CellTest.h"
#include "ArrayOfCellsTest.h"
#include "LineOfCellsTest.h"
#include "HintsFieldTest.h"
#include "CellsFieldTest.h"


int main()
{
	QVector<QObject*> tests;
	
	tests.append(new AddressOfCellTest);
	tests.append(new AddressOfHintTest);
	tests.append(new CellTest);
	tests.append(new ArrayOfCellsTest);
	tests.append(new LineOfCellsTest);
	tests.append(new HintsFieldTest);
	tests.append(new CellsFieldTest);
	
	int result = 0;
	for (int i = 0; i < tests.length(); i++)
	{
		result = QTest::qExec(tests[i]);
		if (result) break;
	}
	qDeleteAll(tests);
	return result;
}
