/**********************************************************************
 * Copyright (C) 2017-2019 Ololuki
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
#include "TimeMeasure.h"
#include <chrono>
#include <QDebug>


TimeMeasure::TimeMeasure()
{
}

TimeMeasure* TimeMeasure::getInstance()
{
	if (self == nullptr)
	{
		self = new TimeMeasure();
		return self;
	} else {
		return self;
	}
}

void TimeMeasure::start()
{
	startTime = std::chrono::high_resolution_clock::now();
}

long long TimeMeasure::nanosecondsPassed()
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startTime).count();
}

void TimeMeasure::printNanosecondsPassed()
{
	qDebug() << nanosecondsPassed();
}

TimeMeasure* TimeMeasure::self = nullptr;
