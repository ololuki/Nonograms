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
#include "HintsFieldModel.h"


HintsFieldModel::HintsFieldModel(int numberOfLines, Orientation o)
  : HintsField(numberOfLines, o)
{
}

HintsFieldModel::~HintsFieldModel()
{
}

void HintsFieldModel::updateHint(Hint hint)
{
	HintsField::updateHint(hint);
	emit lineOfHintsChanged(hint.getAddress().getLine(), hint.getAddress().getOrientation());
}

void HintsFieldModel::insertHintBefore(Hint hint)
{
	HintsField::insertHintBefore(hint);
	emit lineOfHintsChanged(hint.getAddress().getLine(), hint.getAddress().getOrientation());
}

void HintsFieldModel::addHintAtEnd(Hint hint)
{
	HintsField::addHintAtEnd(hint);
	emit lineOfHintsChanged(hint.getAddress().getLine(), hint.getAddress().getOrientation());
}

void HintsFieldModel::deleteHint(Hint hint)
{
	HintsField::deleteHint(hint);
	emit lineOfHintsChanged(hint.getAddress().getLine(), hint.getAddress().getOrientation());
}

void HintsFieldModel::setLineOfHints(LineOfHints line)
{
	if (line.size() < 1) return;
	HintsField::setLineOfHints(line);
	emit lineOfHintsChanged(line[0].getAddress().getLine(), line[0].getAddress().getOrientation());
}
