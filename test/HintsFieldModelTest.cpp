/**********************************************************************
 * Copyright (C) 2017 - 2019 Ololuki
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
#include "HintsFieldModelTest.h"


void HintsFieldModelTest::default_value_of_hint_is_zero()
{
	HintsFieldModel hintsField(numberOfLines, Orientation::VERTICAL);
	QCOMPARE(hintsField.getHint(addressZero).getBlockSize(), 0);
	QCOMPARE(blockValueDefault, 0);
}

void HintsFieldModelTest::number_of_lines_should_increase_after_insert()
{
	HintsFieldModel hintsField(numberOfLines, Orientation::VERTICAL);
	hintsField.insertHintBefore(hintAtZero);
	QCOMPARE(hintsField.numberOfBlocksInLine(lineNumber), 2);
	hintsField.insertHintBefore(hintAtZero);
	QCOMPARE(hintsField.numberOfBlocksInLine(lineNumber), 3);
}

void HintsFieldModelTest::adresses_after_insert_should_be_same_as_count_in_line()
{
	HintsFieldModel hintsField(numberOfLines, Orientation::VERTICAL);
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

void HintsFieldModelTest::value_after_insert_should_be_shifted_properly()
{
	HintsFieldModel hintsField(numberOfLines, Orientation::VERTICAL);
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

void HintsFieldModelTest::number_of_lines_should_not_change_after_update()
{
	HintsFieldModel hintsField(numberOfLines, Orientation::VERTICAL);
	int nuberOfLinesBefore = hintsField.numberOfBlocksInLine(lineNumber);
	hintsField.updateHint(hintAtZero);
	int nuberOfLinesAfter = hintsField.numberOfBlocksInLine(lineNumber);
	QVERIFY(nuberOfLinesBefore == nuberOfLinesAfter);
}

void HintsFieldModelTest::address_should_not_change_after_update()
{
	HintsFieldModel hintsField(numberOfLines, Orientation::VERTICAL);
	Hint hint(addressZero, 555);
	hintsField.updateHint(hint);
	QVERIFY(hintsField.getHint(addressZero).getAddress() == addressZero);
}

void HintsFieldModelTest::block_size_value_should_change_after_update()
{
	HintsFieldModel hintsField(numberOfLines, Orientation::VERTICAL);
	Hint hint(addressZero, 555);
	hintsField.updateHint(hint);
	QCOMPARE(hintsField.getHint(addressZero).getBlockSize(), 555);
}

void HintsFieldModelTest::number_of_hints_in_line_should_decrease_after_delete()
{
	HintsFieldModel hintsField(numberOfLines, Orientation::VERTICAL);
	hintsField.insertHintBefore(hintAtZero);
	hintsField.insertHintBefore(hintAtFirst);
	hintsField.insertHintBefore(hintAtFirst);

	QCOMPARE(hintsField.numberOfBlocksInLine(lineNumber), 4);
	hintsField.deleteHint(hintAtFirst);
	QCOMPARE(hintsField.numberOfBlocksInLine(lineNumber), 3);
	hintsField.deleteHint(hintAtZero);
	QCOMPARE(hintsField.numberOfBlocksInLine(lineNumber), 2);
}

void HintsFieldModelTest::adresses_after_delete_should_be_same_as_count_in_line()
{
	HintsFieldModel hintsField(numberOfLines, Orientation::VERTICAL);
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

void HintsFieldModelTest::hint_can_NOT_be_deleted_if_there_is_only_one_left()
{
	HintsFieldModel containOneHint(numberOfLines, Orientation::VERTICAL);
	QCOMPARE(containOneHint.numberOfBlocksInLine(lineNumber), 1);
	containOneHint.deleteHint(hintAtZero);
	QCOMPARE(containOneHint.numberOfBlocksInLine(lineNumber), 1);
}

void HintsFieldModelTest::values_after_delete_should_be_shifted_properly()
{
	HintsFieldModel hintsField(numberOfLines, Orientation::VERTICAL);
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

void HintsFieldModelTest::getLineOfHints_should_return_valid_line()
{
	HintsFieldModel hintsField(numberOfLines, orientation);
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

void HintsFieldModelTest::setLineOfHints_should_change_hints()
{
	HintsFieldModel hintsField(numberOfLines, orientation);
	LineOfHints line = LineOfHints({hintAtZero, hintAtFirst});

	hintsField.setLineOfHints(line);
	QCOMPARE(hintsField.getHint(addressZero).getBlockSize(), blockValueAtZero);
	QCOMPARE(hintsField.getHint(addressFirst).getBlockSize(), blockValueAtFirst);
	QCOMPARE(hintsField.getHint(addressZero).getAddress(), addressZero);
	QCOMPARE(hintsField.getHint(addressFirst).getAddress(), addressFirst);
}

void HintsFieldModelTest::signal_lineOfHintsChanged_should_be_emited_if_hints_was_changed_by_setLineOfHints()
{
	HintsFieldModel hintsField(numberOfLines, orientation);
	hintsField.insertHintBefore(hintAtZero);

	QSignalSpy spy(&hintsField, &HintsFieldModel::lineOfHintsChanged);

	LineOfHints line = hintsField.getLineOfHints(lineNumber);
	QVERIFY2(line[0].getBlockSize() != anotherBlockValue, "Ensure Hint will be changed");
	line[0].setBlockSize(anotherBlockValue);
	hintsField.setLineOfHints(line);

	const int NUMBER_OF_LINES_CHANGED = 1;
	QCOMPARE(spy.count(), NUMBER_OF_LINES_CHANGED);
	QCOMPARE(qvariant_cast<int>(spy.at(0).at(0)), lineNumber);
	QCOMPARE(qvariant_cast<Orientation>(spy.at(0).at(1)), orientation);
}

void HintsFieldModelTest::getHintsField_should_return_HintsField_with_equal_content()
{
	HintsFieldModel hintsFieldModel(numberOfLines, orientation);
	LineOfHints line = LineOfHints({hintAtZero, hintAtFirst});
	hintsFieldModel.setLineOfHints(line);

	HintsField hintsField = hintsFieldModel.getHintsField();

	QCOMPARE(hintsField.getHint(addressZero).getBlockSize(),
	         hintsFieldModel.getHint(addressZero).getBlockSize());
	QCOMPARE(hintsField.getHint(addressFirst).getBlockSize(),
	         hintsFieldModel.getHint(addressFirst).getBlockSize());
}

void HintsFieldModelTest::setHintsField_should_set_equal_content_as_in_HintsField()
{
	HintsField hintsField(5, Orientation::VERTICAL);
	LineOfHints line = LineOfHints({{addressZero, 3},
	                                {addressFirst, 6},
	                                {addressSecond, 9}
	                               });
	hintsField.setLineOfHints(line);

	// Create HintsFieldModel with different content
	HintsFieldModel hintsFieldModel(10, Orientation::HORIZONTAL);
	LineOfHints lineForModel = LineOfHints({{addressZero, 7},
	                                        {addressFirst, 36},
	                                        {addressSecond, 15},
	                                        {addressThird, 12}
	                                       });
	hintsFieldModel.setLineOfHints(lineForModel);

	hintsFieldModel.setHintsField(hintsField);

	QCOMPARE(hintsFieldModel.getNumberOfLines(),
	         hintsField.getNumberOfLines());
	QCOMPARE(hintsFieldModel.getOrientation(),
	         hintsField.getOrientation());

	QCOMPARE(hintsFieldModel.getHint(addressZero).getBlockSize(),
	         hintsField.getHint(addressZero).getBlockSize());
	QCOMPARE(hintsFieldModel.getHint(addressFirst).getBlockSize(),
	         hintsField.getHint(addressFirst).getBlockSize());
	QCOMPARE(hintsFieldModel.getHint(addressSecond).getBlockSize(),
	         hintsField.getHint(addressSecond).getBlockSize());
}
