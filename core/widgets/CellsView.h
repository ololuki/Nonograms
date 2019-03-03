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
#ifndef CELLSVIEW_H
#define CELLSVIEW_H

#include <memory>
#include <QWidget>
#include "field/CellsField.h"
#include "common/FieldViewConstants.h"
#include "common/DrawableView.h"
#include "controller/action/CellAction.h"


class CellsView : public DrawableView
{
	Q_OBJECT
public:
	explicit CellsView(QWidget *parent = 0);
	virtual ~CellsView();
	void setField(const std::shared_ptr<const CellsField> &field);
	
public slots:
	void onCellChanged(AddressOfCell address);
	
signals:
	void action(CellAction action, AddressOfCell);
	
protected:
	void mousePressEvent(QMouseEvent *event) override;
	
private:
	FieldViewConstants constants;
	void drawGrid();
	void drawOneCell(Cell cell);
	void drawAllCells();
	
	std::shared_ptr<const CellsField> field;
};

#endif // CELLSVIEW_H