/**********************************************************************
 * Copyright (C) 2017 - 2022 Ololuki
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
#include "AddressOfCell.h"


/// Makes invalid address.
/// This c-tor is used in tests and to support
/// passing as queued Signal-Slot parameter and QSignalSpy
AddressOfCell::AddressOfCell() : x(-1), y(-1)
{
}

bool AddressOfCell::isValid() const
{
	return (x >= 0 && y >= 0);
}
