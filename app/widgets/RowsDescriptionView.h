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
#ifndef ROWSDESCRIPTIONVIEW_H
#define ROWSDESCRIPTIONVIEW_H

#include <memory>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include "field/BlocksDescriptionField.h"
#include "field/BlockDescription.h"


class RowsDescriptionView : public QWidget
{
	Q_OBJECT
public:
	explicit RowsDescriptionView(QWidget *parent = 0);
	void setField(std::shared_ptr<BlocksDescriptionField> field);
	
public slots:
	void onDataChanged();
private slots:
	void onInsertingButtonClick();
	
protected:
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
private:
	const int squareSize = 30;		// TODO: move to generalView class
	const int myPenWidth = 1;
	const QColor myPenColor = Qt::black;
	QTextEdit *qTextEdit;
	QPushButton *insertingButton;
	const int insertingButtonWidth = squareSize/2;
	
	QImage image;
	std::shared_ptr<BlocksDescriptionField> field;
	
	bool isPointOnDefinedDescription(QPoint screenPoint);
	void redrawAll();
	void drawOneBlockDescription(BlockDescription blockDescription);
	void drawCleanOneBlock(AddressOnBlocksDescription address);
	void initTextBox();
	void hideTextBox();
	void saveTextBoxToBlockDescription();
	void moveAndShowTextBox(AddressOnBlocksDescription address);
	void initInsertingButton();
	void hideInsertingButton();
	void moveAndShowInsertingButton(AddressOnBlocksDescription address);
	
	void resize(const QSize &newSize);
};

#endif // ROWSDESCRIPTIONVIEW_H
