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
#ifndef HINTSVIEW_H
#define HINTSVIEW_H

#include <memory>
#include <QTextEdit>
#include <QPushButton>
#include "common/DrawableView.h"
#include "common/FieldViewConstants.h"
#include "common/InsertingButtonEventFilter.h"
#include "field/BlocksDescriptionField.h"
#include "controller/action/HintAction.h"


class HintsView : public DrawableView
{
	Q_OBJECT
public:
	explicit HintsView(QWidget *parent = 0);
	void setField(const std::shared_ptr<const BlocksDescriptionField> &field);
	
signals:
	// signals emited to controller
	void action(HintAction action, AddressOnBlocksDescription address);
	void action(HintAction action, BlockDescription blockDescription);
	
public slots:
	// invoked by model to inform about changes
	void onDataChanged();
	// invoked by model to inform about changes
	void onLineOfHintsChanged(AddressOnBlocksDescription address);
	// invoked by controller
	void showInsertingButtonBefore(AddressOnBlocksDescription address);
	// invoked by controller
	void showDescriptionEditingBox(AddressOnBlocksDescription address);
	
private slots:
	void onInsertingButtonClick();
	
protected:
	FieldViewConstants constants;
	QTextEdit *qTextEdit;
	std::shared_ptr<QPushButton> insertingButton;
	const int insertingButtonHeight = constants.squareSize/2;
	
	std::shared_ptr<const BlocksDescriptionField> field;
	
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	
	bool isPointOnDefinedDescription(QPoint screenPoint);
	void redrawAll();
	void drawOneBlockDescription(BlockDescription blockDescription);
	void drawCleanOneBlock(AddressOnBlocksDescription address);
	void initTextBox();
	void hideTextBox();
	void saveTextBoxToHint();
	void moveAndShowTextBox(AddressOnBlocksDescription address);
	void initInsertingButton();
	void hideInsertingButton();
	void moveAndShowInsertingButton(AddressOnBlocksDescription address);
	
private:
	AddressOnBlocksDescription::orientation orientation;
	InsertingButtonEventFilter insertingButtonEventFilter;
};

#endif // HINTSVIEW_H
