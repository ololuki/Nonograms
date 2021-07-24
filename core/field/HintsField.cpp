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
#include "HintsField.h"
#include <QDebug>


/// Make invalid hints field
HintsField::HintsField()
{
	numberOfLines = 0;
	orientation = Orientation::HORIZONTAL;
}

HintsField::HintsField(int numberOfLines, Orientation o)
{
	this->numberOfLines = numberOfLines;
	this->orientation = o;
	const int defaultBlockSize = 0;
	for(int i = 0; i < numberOfLines; i++)
	{
		AddressOfHint address = AddressOfHint(orientation, i, 0);
		NVector<Hint> line;
		line.push_back(Hint(address, defaultBlockSize));
		linesOfHints.push_back(line);
	}
}

HintsField::HintsField(const HintsField& hintsField)
  : numberOfLines(hintsField.numberOfLines),
    orientation(hintsField.orientation),
    linesOfHints(hintsField.linesOfHints)
{
	qDebug() << "HintsField::HintsField(const HintsField& hintsField)";
}

/// Build HintsField based on list of lines
/// For vertical first line is on left
/// For horizontal first row is on top
/// This could be used in tests to make field from strings
/// representing lines of hints for nonogram
HintsField::HintsField(Orientation o, std::initializer_list<LineOfHints> lines)
  : numberOfLines(static_cast<int>(lines.size())),
    orientation(o)
{
	int lineNumber = 0;
	for (auto row : lines)
	{
		NVector<Hint> lineOfHints;
		for (int i = 0; i < row.size(); i++)
		{
			lineOfHints.push_back(Hint(AddressOfHint(o, lineNumber, i),
			                           row[i].getBlockSize(),
			                           row[i].getCellSign()));
		}
		linesOfHints.push_back(LineOfHints(lineOfHints));
		++lineNumber;
	}
}

HintsField::~HintsField()
{
}

bool HintsField::operator==(const HintsField& other) const
{
	if (orientation == other.orientation)
	{
		return linesOfHints == other.linesOfHints;
	}
	return false;
}

bool HintsField::operator!=(const HintsField& other) const
{
	if (orientation != other.orientation)
	{
		return true;
	}
	return linesOfHints != other.linesOfHints;
}

const Hint& HintsField::getHint(AddressOfHint address) const
{
	return linesOfHints[address.getLine()][address.getCount()];
}

void HintsField::updateHint(Hint hint)
{
	int line = hint.getAddress().getLine();
	linesOfHints[line].updateHint(hint);
}

void HintsField::insertHintBefore(Hint hint)
{
	int line = hint.getAddress().getLine();
	linesOfHints[line].insertHintBefore(hint);
}

void HintsField::addHintAtEnd(Hint hint)
{
	int line = hint.getAddress().getLine();
	int count = hint.getAddress().getCount();
	if (linesOfHints[line].size() == count)
	{
		linesOfHints[line].push_back(hint);
	}
}

void HintsField::deleteHint(Hint hint)
{
	int line = hint.getAddress().getLine();
	int count = hint.getAddress().getCount();
	if (linesOfHints[line].size() <= 1) return;
	int newLength = linesOfHints[line].size() - 1;
	for(int i = count; i < newLength; i++)
	{
		linesOfHints[line][i].setBlockSize(linesOfHints[line][i+1].getBlockSize());
	}
	linesOfHints[line].pop_back();
}

int HintsField::numberOfBlocksInLine(int lineNumber) const
{
	return linesOfHints[lineNumber].size();
}

int HintsField::getNumberOfLines() const
{
	return numberOfLines;
}

int HintsField::allHintsLength() const
{
	int length = 0;
	for (int i = 0; i < numberOfLines; i++)
	{
		length = (numberOfBlocksInLine(i) > length) ? numberOfBlocksInLine(i) : length;
	}
	return length;
}

Orientation HintsField::getOrientation() const
{
	return orientation;
}

bool HintsField::isDefinedHintAt(AddressOfHint address) const
{
	int line = address.getLine();
	if (line >= linesOfHints.size()) return false;
	if (address.getCount() >= linesOfHints[line].size()) return false;
	return true;
}

LineOfHints HintsField::getLineOfHints(int lineNumber)
{
	return linesOfHints[lineNumber];
}

void HintsField::setLineOfHints(LineOfHints line)
{
	if (line.size() < 1) return;
	int lineNumber = line[0].getAddress().getLine();
	linesOfHints[lineNumber] = line;
}

///
/// Returns a textual representation of HintsField
/// for testing and debugging.
/// \return std::string with readable contents of HintsField
///
std::string HintsField::toStdString() const
{
	std::string str = "HinstField ";
	str += (orientation == Orientation::HORIZONTAL) ? "Horizontal" : "Vertical";
	str += "\n";
	for (auto line : linesOfHints)
	{
		str += line.toStdString();
		str += "\n";
	}
	return str;
}

///
/// Returns a textual representation of HintsField.
/// This function is used by QCOMPARE() to output verbose
/// information in case of a test failure.
/// The caller of toString() must delete the returned data using delete[].
/// \param hints
/// \return pointer to c string alocated with new[]
///
char *toString(const HintsField& hints)
{
	return qstrdup(hints.toStdString().c_str());
}
