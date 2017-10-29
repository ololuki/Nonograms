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
#include "DrawingAreaView.h"
#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QSize>


DrawingAreaView::DrawingAreaView(QWidget *parent)
    : DrawableView(parent)
{
	
}

DrawingAreaView::~DrawingAreaView()
{
	
}

void DrawingAreaView::setField(const std::shared_ptr<const DrawingAreaField> &field)
{
	this->field = field;
	connect(
		static_cast<const DrawingAreaField*>(this->field.get()),
		&DrawingAreaField::pixelChanged,
		this,
		&DrawingAreaView::onPixelChanged
	);
	
	int sizeX = field->getWidth() * constants.squareSize + 1;
	int sizeY = field->getHeight() * constants.squareSize + 1;
	QSize size(sizeX, sizeY);
	resize(size);
	drawAllPixels();
}

void DrawingAreaView::drawAllPixels()
{
	for (int y = 0; y < field->getHeight(); y++)
	{
		for (int x = 0; x < field->getWidth(); x++)
		{
			AddressOnDrawingArea address(x, y);
			drawOnePixel(field->getPixel(address));
		}
	}
	drawGrid();
	update();
}

void DrawingAreaView::onPixelChanged(AddressOnDrawingArea address)
{
	drawOnePixel(field->getPixel(address));
	update();
}

void DrawingAreaView::mousePressEvent(QMouseEvent *event)
{
	QPoint currentPoint = event->pos();
	
	int pixelX = currentPoint.x() / constants.squareSize;
	int pixelY = currentPoint.y() / constants.squareSize;
	
	if (pixelX >= field->getWidth()) return;
	if (pixelY >= field->getHeight()) return;
	
	CellAction cellAction;
	switch(event->button())
	{
	case Qt::LeftButton:
		cellAction = CellAction::MakeFilledBlack;
		break;
	case Qt::RightButton:
		cellAction = CellAction::MakeDot;
		break;
	case Qt::MiddleButton:
		cellAction = CellAction::MakeEmpty;
		break;
	}
	emit action(cellAction, AddressOnDrawingArea(pixelX, pixelY));
}

void DrawingAreaView::drawGrid()
{
	QPainter p(&image);
	p.setPen(QPen(constants.myPenColor, constants.myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	for (int y = 0; y < field->getHeight(); y++)
	{
		for (int x = 0; x < field->getWidth(); x++)
		{
			int currentX = x * constants.squareSize;
			int currentY = y * constants.squareSize;
			QRect rectangle = QRect(currentX, currentY, constants.squareSize, constants.squareSize);
			p.drawRect(rectangle);
		}
	}
}

void DrawingAreaView::drawOnePixel(Pixel pixel)
{
	QPainter painter(&image);
	painter.setPen(QPen(constants.myPenColor, constants.myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	
	int x = pixel.getAddress().getX();
	int y = pixel.getAddress().getY();
	
	int currentX = x * constants.squareSize;
	int currentY = y * constants.squareSize;
	QRect rectangle = QRect(currentX, currentY, constants.squareSize, constants.squareSize);
	
	if (pixel.isFilledBlack()) {
		painter.fillRect(rectangle, Qt::black);
	} else if (pixel.isDot()) {
		painter.fillRect(rectangle, Qt::white);
		QPoint centerP(currentX + constants.squareSize / 2, currentY + constants.squareSize / 2);
		painter.drawEllipse(centerP, constants.squareSize / 10, constants.squareSize / 10);
	}else if (pixel.isEmpty()) {
		painter.fillRect(rectangle, Qt::white);
	}
	painter.drawRect(rectangle);
}
