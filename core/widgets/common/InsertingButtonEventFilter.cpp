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
#include "InsertingButtonEventFilter.h"
#include <QPushButton>
#include <QMouseEvent>


bool InsertingButtonEventFilter::eventFilter(QObject *obj, QEvent *event)
{
	QPushButton * btn = static_cast<QPushButton *>(obj);
	QMouseEvent * mouseEvent = static_cast<QMouseEvent *>(event);
	switch (event->type())
	{
	case QEvent::MouseButtonPress:
		if (mouseEvent->button() == Qt::LeftButton)
		{
			btn->setDown(true);
		}
		return true;
	case QEvent::MouseButtonRelease:
		if (mouseEvent->button() == Qt::LeftButton)
		{
			btn->setDown(false);
			btn->clicked();
		}
		return true;
	case QEvent::MouseButtonDblClick:
		return true;
	default:
		return QObject::eventFilter(obj, event);
	}
}
