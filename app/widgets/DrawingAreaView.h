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
#ifndef DRAWINGAREAVIEW_H
#define DRAWINGAREAVIEW_H

#include <memory>
#include <QWidget>
#include "field/DrawingAreaField.h"
#include "common/FieldViewConstants.h"
#include "common/DrawableView.h"


class DrawingAreaView : public DrawableView
{
	Q_OBJECT
public:
	explicit DrawingAreaView(QWidget *parent = 0);
	virtual ~DrawingAreaView();
	void setField(const std::shared_ptr<const DrawingAreaField> &field);
	
public slots:
	void onPixelChanged(AddressOnDrawingArea address);
	
signals:
	void mousePressed(Qt::MouseButton MouseButton, AddressOnDrawingArea);
	
protected:
	void mousePressEvent(QMouseEvent *event) override;
	
private:
	FieldViewConstants constants;
	void drawGrid();
	void drawOnePixel(Pixel pixel);
	void drawAllPixels();
	
	std::shared_ptr<const DrawingAreaField> field;
};

#endif // DRAWINGAREAVIEW_H
