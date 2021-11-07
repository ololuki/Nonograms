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
#ifndef HINTSVIEW_H
#define HINTSVIEW_H

#include <memory>
#include <QTextEdit>
#include <QPushButton>
#include "common/DrawableView.h"
#include "common/FieldViewConstants.h"
#include "common/InsertingButtonEventFilter.h"
#include "controller/action/HintAction.h"
#include "field/AddressOfHint.h"
#include "field/Hint.h"

class HintsFieldModel;


class HintsView : public DrawableView
{
	Q_OBJECT
public:
	explicit HintsView(QWidget *parent = nullptr);
	void setField(const std::shared_ptr<const HintsFieldModel> &field);

signals:
	// signals emited to controller
	void action(HintAction action, AddressOfHint address);
	void action(HintAction action, Hint hint);

public slots:
	// invoked by model to inform about changes
	void onLineOfHintsChanged(int lineNumber, Orientation orientation);
	void onHintsChanged();
	// invoked by controller
	void onShowInsertingButtonBefore(AddressOfHint address);
	// invoked by controller
	void onShowHintEditingBox(AddressOfHint address);

private slots:
	void onInsertingButtonClick();

protected:
	FieldViewConstants constants;
	QTextEdit *qTextEdit;
	std::shared_ptr<QPushButton> insertingButton;
	const int insertingButtonHeight = constants.squareSize/2;

	std::shared_ptr<const HintsFieldModel> field;

	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

	bool isPointOnDefinedHint(QPoint screenPoint);
	void redrawAll();
	void drawOneHint(Hint hint);
	void undrawOneHint(AddressOfHint address);
	void initTextBox();
	void hideTextBox();
	void saveTextBoxToHint();
	void moveAndShowTextBox(AddressOfHint address);
	void initInsertingButton();
	void hideInsertingButton();
	void moveAndShowInsertingButton(AddressOfHint address);

private:
	QSize calculateSize();
	Orientation orientation;
	InsertingButtonEventFilter insertingButtonEventFilter;
};

#endif // HINTSVIEW_H
