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
#include "HintsFieldTest.h"

Q_DECLARE_METATYPE(HintsField)


void HintsFieldTest::constructor_initializer_list_horizontal()
{
	HintsField hintsField(
	            Orientation::HORIZONTAL,
	{
	    LineOfHints({Hint(3), Hint(5)}),
	    LineOfHints({Hint(1), {Hint(3)}}),
	    LineOfHints({Hint(0)}),
	    LineOfHints({Hint(105), Hint(13), Hint(5)})
	});

	QCOMPARE(hintsField.getNumberOfLines(), 4);
	QCOMPARE(hintsField.allHintsLength(), 3);
	QCOMPARE(hintsField.getOrientation(), Orientation::HORIZONTAL);
	QVERIFY(hintsField.getHint({Orientation::HORIZONTAL, 0, 0}).getBlockSize() == 3);
	QVERIFY(hintsField.getHint({Orientation::HORIZONTAL, 0, 1}).getBlockSize() == 5);
}

void HintsFieldTest::constructor_initializer_list_vertical()
{
	HintsField hintsField(
	            Orientation::VERTICAL,
	{
	    LineOfHints({Hint(3), Hint(5)}),
	    LineOfHints({Hint(1), {Hint(3)}}),
	    LineOfHints({Hint(0)}),
	    LineOfHints({Hint(105), Hint(13), Hint(5)})
	});

	QCOMPARE(hintsField.getNumberOfLines(), 4);
	QCOMPARE(hintsField.allHintsLength(), 3);
	QCOMPARE(hintsField.getOrientation(), Orientation::VERTICAL);
	QVERIFY(hintsField.getHint({Orientation::VERTICAL, 0, 0}).getBlockSize() == 3);
	QVERIFY(hintsField.getHint({Orientation::VERTICAL, 0, 1}).getBlockSize() == 5);
}

/// Empty initializer list should make empty HintsField
void HintsFieldTest::constructor_initializer_list_empty_list_make_empty()
{
	HintsField hintsField(Orientation::VERTICAL, {});

	QCOMPARE(hintsField.getNumberOfLines(), 0);
	QCOMPARE(hintsField.allHintsLength(), 0);
}

void HintsFieldTest::equality_opeators_compare_cell_sign_equal_data()
{
	QTest::addColumn<HintsField>("d_fieldA");
	QTest::addColumn<HintsField>("d_fieldB");

	QTest::newRow("empty") << HintsField() << HintsField();

	QTest::newRow("1 column") << HintsField{1, Orientation::VERTICAL}
	                          << HintsField{1, Orientation::VERTICAL};

	QTest::newRow("1 row") << HintsField{1, Orientation::HORIZONTAL}
	                       << HintsField{1, Orientation::HORIZONTAL};

	QTest::newRow("1 column with Hints")
	        << HintsField{Orientation::VERTICAL, {LineOfHints({Hint(5), Hint(9)})}}
	        << HintsField{Orientation::VERTICAL, {LineOfHints({Hint(5), Hint(9)})}};

	QTest::newRow("1 row with Hints")
	        << HintsField{Orientation::HORIZONTAL, {LineOfHints({Hint(15), Hint(2)})}}
	        << HintsField{Orientation::HORIZONTAL, {LineOfHints({Hint(15), Hint(2)})}};

	QTest::newRow("3 columns")
	        << HintsField{
	           Orientation::VERTICAL, {
	           LineOfHints({Hint(1)}),
	           LineOfHints({Hint(5), Hint(9)}),
	           LineOfHints({Hint(13)}) }}
	        << HintsField{
	           Orientation::VERTICAL, {
	           LineOfHints({Hint(1)}),
	           LineOfHints({Hint(5), Hint(9)}),
	           LineOfHints({Hint(13)}) }};
}

void HintsFieldTest::equality_opeators_compare_cell_sign_equal()
{
	QFETCH(HintsField, d_fieldA);
	QFETCH(HintsField, d_fieldB);

	QCOMPARE(d_fieldA, d_fieldB);
	QVERIFY(d_fieldA == d_fieldB);
	QCOMPARE(d_fieldA != d_fieldB, false);
}

void HintsFieldTest::equality_opeators_compare_cell_sign_not_equal_data()
{
	QTest::addColumn<HintsField>("d_fieldA");
	QTest::addColumn<HintsField>("d_fieldB");

	QTest::newRow("different orientation")
	        << HintsField{1, Orientation::VERTICAL}
	        << HintsField{1, Orientation::HORIZONTAL};

	QTest::newRow("different number of rows")
	        << HintsField{5, Orientation::HORIZONTAL}
	        << HintsField{1, Orientation::HORIZONTAL};

	QTest::newRow("1 column with 1 Hint - different blockSize")
	        << HintsField{Orientation::VERTICAL, {LineOfHints({Hint(5)})}}
	        << HintsField{Orientation::VERTICAL, {LineOfHints({Hint(4)})}};

	QTest::newRow("1 column with 1 Hint - different cellSign")
	        << HintsField{Orientation::VERTICAL, {LineOfHints({Hint(4, cellSign::SGN_FILLED)})}}
	        << HintsField{Orientation::VERTICAL, {LineOfHints({Hint(4, cellSign::SGN_FILL_BLACK)})}};

	QTest::newRow("1 column with 2 Hints")
	        << HintsField{Orientation::VERTICAL, {LineOfHints({Hint(9), Hint(5)})}}
	        << HintsField{Orientation::VERTICAL, {LineOfHints({Hint(9), Hint(4)})}};

	QTest::newRow("3 columns")
	        << HintsField{
	           Orientation::VERTICAL, {
	           LineOfHints({Hint(1)}),
	           LineOfHints({Hint(5), Hint(9)}),
	           LineOfHints({Hint(13)}) }}
	        << HintsField{
	           Orientation::VERTICAL, {
	           LineOfHints({Hint(1)}),
	           LineOfHints({Hint(5), Hint(9)}),
	           LineOfHints({Hint(2)}) }};

	QTest::newRow("3 columns/rows with different orientation only")
	        << HintsField{
	           Orientation::VERTICAL, {
	           LineOfHints({Hint(1)}),
	           LineOfHints({Hint(5), Hint(9)}),
	           LineOfHints({Hint(13)}) }}
	        << HintsField{
	           Orientation::HORIZONTAL, {
	           LineOfHints({Hint(1)}),
	           LineOfHints({Hint(5), Hint(9)}),
	           LineOfHints({Hint(13)}) }};

	QTest::newRow("3 columns with different number of Hints in one row - more in second")
	        << HintsField{
	           Orientation::VERTICAL, {
	           LineOfHints({Hint(1)}),
	           LineOfHints({Hint(5), Hint(9)}),
	           LineOfHints({Hint(13)}) }}
	        << HintsField{
	           Orientation::VERTICAL, {
	           LineOfHints({Hint(1), Hint(5)}),
	           LineOfHints({Hint(5), Hint(9)}),
	           LineOfHints({Hint(13)}) }};

	QTest::newRow("3 columns with different number of Hints in one row - more in first")
	        << HintsField{
	           Orientation::VERTICAL, {
	           LineOfHints({Hint(1), Hint(5)}),
	           LineOfHints({Hint(5), Hint(9)}),
	           LineOfHints({Hint(13)}) }}
	        << HintsField{
	           Orientation::VERTICAL, {
	           LineOfHints({Hint(1)}),
	           LineOfHints({Hint(5), Hint(9)}),
	           LineOfHints({Hint(13)}) }};

	QTest::newRow("different number of columns with same data")
	        << HintsField{
	           Orientation::VERTICAL, {
	           LineOfHints({Hint(1)}),
	           LineOfHints({Hint(5), Hint(9)}),
	           LineOfHints({Hint(13)}) }}
	        << HintsField{
	           Orientation::VERTICAL, {
	           LineOfHints({Hint(1)}),
	           LineOfHints({Hint(5), Hint(9)}) }};

	HintsField someHintsField{
		Orientation::HORIZONTAL, {
			LineOfHints({Hint(1)}),
			LineOfHints({Hint(3), Hint(9)}),
			LineOfHints({Hint(5)}) }};
	HintsField copiedHintsField(someHintsField);
	copiedHintsField.updateHint({AddressOfHint(Orientation::HORIZONTAL, 0, 0), 25});
	QTest::newRow("copy and modify") << someHintsField << copiedHintsField;
}

void HintsFieldTest::equality_opeators_compare_cell_sign_not_equal()
{
	QFETCH(HintsField, d_fieldA);
	QFETCH(HintsField, d_fieldB);

	QCOMPARE(d_fieldA == d_fieldB, false);
	QVERIFY(d_fieldA != d_fieldB);
}

void HintsFieldTest::default_value_of_hint_is_zero()
{
	HintsField hintsField(numberOfLines, Orientation::VERTICAL);
	QCOMPARE(hintsField.getHint(addressZero).getBlockSize(), 0);
	QCOMPARE(blockValueDefault, 0);
}

void HintsFieldTest::number_of_lines_should_increase_after_insert()
{
	HintsField hintsField(numberOfLines, Orientation::VERTICAL);
	hintsField.insertHintBefore(hintAtZero);
	QCOMPARE(hintsField.numberOfBlocksInLine(lineNumber), 2);
	hintsField.insertHintBefore(hintAtZero);
	QCOMPARE(hintsField.numberOfBlocksInLine(lineNumber), 3);
}

void HintsFieldTest::adresses_after_insert_should_be_same_as_count_in_line()
{
	HintsField hintsField(numberOfLines, Orientation::VERTICAL);
	hintsField.insertHintBefore(hintAtZero);
	QVERIFY(hintsField.getHint(addressZero).getAddress() == addressZero);
	QVERIFY(hintsField.getHint(addressFirst).getAddress() == addressFirst);
	hintsField.insertHintBefore(hintAtFirst);
	QVERIFY(hintsField.getHint(addressZero).getAddress() == addressZero);
	QVERIFY(hintsField.getHint(addressFirst).getAddress() == addressFirst);
	QVERIFY(hintsField.getHint(addressSecond).getAddress() == addressSecond);
	hintsField.insertHintBefore(hintAtZero);
	QVERIFY(hintsField.getHint(addressZero).getAddress() == addressZero);
	QVERIFY(hintsField.getHint(addressFirst).getAddress() == addressFirst);
	QVERIFY(hintsField.getHint(addressSecond).getAddress() == addressSecond);
	QVERIFY(hintsField.getHint(addressThird).getAddress() == addressThird);
}

void HintsFieldTest::value_after_insert_should_be_shifted_properly()
{
	HintsField hintsField(numberOfLines, Orientation::VERTICAL);
	hintsField.insertHintBefore(hintAtZero);
	QVERIFY(hintsField.getHint(addressZero).getBlockSize() == blockValueAtZero);
	QVERIFY(hintsField.getHint(addressFirst).getBlockSize() == blockValueDefault);
	hintsField.insertHintBefore(hintAtFirst);
	QVERIFY(hintsField.getHint(addressZero).getBlockSize() == blockValueAtZero);
	QVERIFY(hintsField.getHint(addressFirst).getBlockSize() == blockValueAtFirst);
	QVERIFY(hintsField.getHint(addressSecond).getBlockSize() == blockValueDefault);
	hintsField.insertHintBefore(hintAtFirst);
	QVERIFY(hintsField.getHint(addressZero).getBlockSize() == blockValueAtZero);
	QVERIFY(hintsField.getHint(addressFirst).getBlockSize() == blockValueAtFirst);
	QVERIFY(hintsField.getHint(addressSecond).getBlockSize() == blockValueAtFirst);
	QVERIFY(hintsField.getHint(addressThird).getBlockSize() == blockValueDefault);
}

void HintsFieldTest::number_of_lines_should_not_change_after_update()
{
	HintsField hintsField(numberOfLines, Orientation::VERTICAL);
	int nuberOfLinesBefore = hintsField.numberOfBlocksInLine(lineNumber);
	hintsField.updateHint(hintAtZero);
	int nuberOfLinesAfter = hintsField.numberOfBlocksInLine(lineNumber);
	QVERIFY(nuberOfLinesBefore == nuberOfLinesAfter);
}

void HintsFieldTest::address_should_not_change_after_update()
{
	HintsField hintsField(numberOfLines, Orientation::VERTICAL);
	Hint hint(addressZero, 555);
	hintsField.updateHint(hint);
	QVERIFY(hintsField.getHint(addressZero).getAddress() == addressZero);
}

void HintsFieldTest::block_size_value_should_change_after_update()
{
	HintsField hintsField(numberOfLines, Orientation::VERTICAL);
	Hint hint(addressZero, 555);
	hintsField.updateHint(hint);
	QCOMPARE(hintsField.getHint(addressZero).getBlockSize(), 555);
}

void HintsFieldTest::number_of_hints_in_line_should_decrease_after_delete()
{
	HintsField hintsField(numberOfLines, Orientation::VERTICAL);
	hintsField.insertHintBefore(hintAtZero);
	hintsField.insertHintBefore(hintAtFirst);
	hintsField.insertHintBefore(hintAtFirst);

	QCOMPARE(hintsField.numberOfBlocksInLine(lineNumber), 4);
	hintsField.deleteHint(hintAtFirst);
	QCOMPARE(hintsField.numberOfBlocksInLine(lineNumber), 3);
	hintsField.deleteHint(hintAtZero);
	QCOMPARE(hintsField.numberOfBlocksInLine(lineNumber), 2);
}

void HintsFieldTest::adresses_after_delete_should_be_same_as_count_in_line()
{
	HintsField hintsField(numberOfLines, Orientation::VERTICAL);
	hintsField.insertHintBefore(hintAtZero);
	hintsField.insertHintBefore(hintAtFirst);
	hintsField.insertHintBefore(hintAtFirst);

	QVERIFY(hintsField.getHint(addressZero).getAddress() == addressZero);
	QVERIFY(hintsField.getHint(addressFirst).getAddress() == addressFirst);
	QVERIFY(hintsField.getHint(addressSecond).getAddress() == addressSecond);
	QVERIFY(hintsField.getHint(addressThird).getAddress() == addressThird);
	hintsField.deleteHint(hintAtZero);
	QVERIFY(hintsField.getHint(addressZero).getAddress() == addressZero);
	QVERIFY(hintsField.getHint(addressFirst).getAddress() == addressFirst);
	QVERIFY(hintsField.getHint(addressSecond).getAddress() == addressSecond);
	hintsField.deleteHint(hintAtZero);
	QVERIFY(hintsField.getHint(addressZero).getAddress() == addressZero);
	QVERIFY(hintsField.getHint(addressFirst).getAddress() == addressFirst);
}

void HintsFieldTest::hint_can_NOT_be_deleted_if_there_is_only_one_left()
{
	HintsField containOneHint(numberOfLines, Orientation::VERTICAL);
	QCOMPARE(containOneHint.numberOfBlocksInLine(lineNumber), 1);
	containOneHint.deleteHint(hintAtZero);
	QCOMPARE(containOneHint.numberOfBlocksInLine(lineNumber), 1);
}

void HintsFieldTest::values_after_delete_should_be_shifted_properly()
{
	HintsField hintsField(numberOfLines, Orientation::VERTICAL);
	hintsField.insertHintBefore(hintAtZero);
	hintsField.insertHintBefore(hintAtFirst);
	hintsField.insertHintBefore(hintAtFirst);

	QCOMPARE(hintsField.getHint(addressZero).getBlockSize(), blockValueAtZero);
	QCOMPARE(hintsField.getHint(addressFirst).getBlockSize(), blockValueAtFirst);
	QCOMPARE(hintsField.getHint(addressSecond).getBlockSize(), blockValueAtFirst);
	QCOMPARE(hintsField.getHint(addressThird).getBlockSize(), blockValueDefault);
	hintsField.deleteHint(hintAtZero);
	QCOMPARE(hintsField.getHint(addressZero).getBlockSize(), blockValueAtFirst);
	QCOMPARE(hintsField.getHint(addressFirst).getBlockSize(), blockValueAtFirst);
	QCOMPARE(hintsField.getHint(addressSecond).getBlockSize(), blockValueDefault);
	hintsField.deleteHint(hintAtZero);
	QCOMPARE(hintsField.getHint(addressZero).getBlockSize(), blockValueAtFirst);
	QCOMPARE(hintsField.getHint(addressFirst).getBlockSize(), blockValueDefault);
	hintsField.deleteHint(hintAtFirst);
	QCOMPARE(hintsField.getHint(addressZero).getBlockSize(), blockValueAtFirst);
}

void HintsFieldTest::getLineOfHints_should_return_valid_line()
{
	HintsField hintsField(numberOfLines, orientation);
	hintsField.insertHintBefore(hintAtZero);
	hintsField.insertHintBefore(hintAtFirst);

	LineOfHints line = hintsField.getLineOfHints(lineNumber);
	QCOMPARE(line[0].getBlockSize(), blockValueAtZero);
	QCOMPARE(line[1].getBlockSize(), blockValueAtFirst);
	QCOMPARE(line[2].getBlockSize(), blockValueDefault);
	QCOMPARE(line[0].getAddress(), addressZero);
	QCOMPARE(line[1].getAddress(), addressFirst);
	QCOMPARE(line[2].getAddress(), addressSecond);
}

void HintsFieldTest::setLineOfHints_should_change_hints()
{
	HintsField hintsField(numberOfLines, orientation);
	LineOfHints line = LineOfHints({hintAtZero, hintAtFirst});

	hintsField.setLineOfHints(line);
	QCOMPARE(hintsField.getHint(addressZero).getBlockSize(), blockValueAtZero);
	QCOMPARE(hintsField.getHint(addressFirst).getBlockSize(), blockValueAtFirst);
	QCOMPARE(hintsField.getHint(addressZero).getAddress(), addressZero);
	QCOMPARE(hintsField.getHint(addressFirst).getAddress(), addressFirst);
}
