/**********************************************************************
 * Copyright (C) 2022 Ololuki
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
#ifndef FINISHEDBLOCKSLINESPLITTERTEST_H
#define FINISHEDBLOCKSLINESPLITTERTEST_H

#include <QtTest>


class FinishedBlocksLineSplitterTest : public QObject
{
	Q_OBJECT
private slots:
	void first_finished_and_few_empty_returns_one_shorter_subline();
	void last_finished_and_few_empty_returns_one_shorter_subline();
	void all_finished_returns_empty_list();
	void none_finished_returns_empty_list();
};

#endif // FINISHEDBLOCKSLINESPLITTERTEST_H
