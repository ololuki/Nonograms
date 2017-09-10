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
#include "RowsDescriptionView.h"

#include <QPainter>
#include <QRect>
#include <QPaintEvent>
#include <QStaticText>


RowsDescriptionView::RowsDescriptionView(QWidget *parent)
	: DrawableView(parent)
{
	initTextBox();
	initInsertingButton();
}

void RowsDescriptionView::setField(std::shared_ptr<BlocksDescriptionField> field)
{
	this->field = field;
	connect(static_cast<BlocksDescriptionField*>(this->field.get()), &BlocksDescriptionField::blocksDescriptionChanged, this, &RowsDescriptionView::onDataChanged);
	
	int widthInSquares = 3;
	int screenX = widthInSquares * constants.squareSize + constants.myPenWidth;
	int screenY = static_cast<int>(field->getNumberOfLines()) * constants.squareSize + constants.myPenWidth;
	QSize size(screenX, screenY);
	resize(size);
	onDataChanged();
}

void RowsDescriptionView::onDataChanged()
{
	size_t currentWidth = static_cast<size_t>(minimumWidth() / constants.squareSize);
	if (field->allBlocksDescriptionLength() > currentWidth)
	{
		int newWidthInSquares = static_cast<int>(field->allBlocksDescriptionLength());
		int screenX = newWidthInSquares * constants.squareSize + constants.myPenWidth;
		int screenY = static_cast<int>(field->getNumberOfLines()) * constants.squareSize + constants.myPenWidth;
		QSize size(screenX, screenY);
		resize(size);
	}
	redrawAll();
}

void RowsDescriptionView::onInsertingButtonClick()
{
	size_t count = static_cast<size_t>((insertingButton->pos().x() + constants.squareSize) / constants.squareSize);
	size_t row = static_cast<size_t>(insertingButton->pos().y() / constants.squareSize);
	
	AddressOnBlocksDescription address = AddressOnBlocksDescription(AddressOnBlocksDescription::HORIZONTAL, row, count);
	if (count < field->numberOfBlocksInLine(row))
	{
		field->insertDescriptionBefore(BlockDescription(address, 0));
	}
	else if (count == field->numberOfBlocksInLine(row))
	{
		field->addDescriptionAtEnd(BlockDescription(address, 0));
	}
}

void RowsDescriptionView::mousePressEvent(QMouseEvent *event)
{
	saveTextBoxToBlockDescription();
	QPoint screenPoint = event->pos();
	if (isPointOnDefinedDescription(screenPoint))
	{
		size_t count = static_cast<size_t>(screenPoint.x() / constants.squareSize);
		size_t row = static_cast<size_t>(screenPoint.y() / constants.squareSize);
		AddressOnBlocksDescription address(AddressOnBlocksDescription::orientation::HORIZONTAL, row, count);
		if (event->button() == Qt::LeftButton)
		{
			moveAndShowTextBox(address);
		}
		else if (event->button() == Qt::RightButton)
		{
			hideTextBox();
			field->deleteDescription(BlockDescription(address, 0));
		}
	} else {
		hideTextBox();
	}
}

void RowsDescriptionView::mouseMoveEvent(QMouseEvent *event)
{
	QPoint screenPoint = event->pos();
	int halfSquareSize = constants.squareSize/2;
	size_t line = static_cast<size_t>(screenPoint.y() / constants.squareSize);
	size_t count = static_cast<size_t>((screenPoint.x() + halfSquareSize) / constants.squareSize);
	AddressOnBlocksDescription address(AddressOnBlocksDescription::orientation::HORIZONTAL, line, count);
	if ((screenPoint.x() + insertingButtonWidth/2) % constants.squareSize < insertingButtonWidth)
	{
		screenPoint.setX(screenPoint.x() - insertingButtonWidth/2);	// remap to area with defined descriptions + area for half of insertButtons
		if(isPointOnDefinedDescription(screenPoint))
			moveAndShowInsertingButton(address);
		else
			hideInsertingButton();
	} else {
		hideInsertingButton();
	}
}

bool RowsDescriptionView::isPointOnDefinedDescription(QPoint screenPoint)
{
	size_t count = static_cast<size_t>(screenPoint.x() / constants.squareSize);
	size_t line = static_cast<size_t>(screenPoint.y() / constants.squareSize);
	AddressOnBlocksDescription address = AddressOnBlocksDescription(AddressOnBlocksDescription::HORIZONTAL, line, count);
	return (field->isDefinedDescriptionAt(address));
}

void RowsDescriptionView::redrawAll()
{
	for(size_t i = 0; i < field->getNumberOfLines(); i++)
	{
		size_t numberOfBlocksInLine = field->numberOfBlocksInLine(i);
		AddressOnBlocksDescription addressAfterLine = AddressOnBlocksDescription(AddressOnBlocksDescription::HORIZONTAL, i, numberOfBlocksInLine);
		drawCleanOneBlock(addressAfterLine);
	}
	for(size_t i = 0; i < field->getNumberOfLines(); i++)
	{
		size_t numberOfBlocksInLine = field->numberOfBlocksInLine(i);
		for(size_t j = 0; j < numberOfBlocksInLine; j++)
		{
			AddressOnBlocksDescription address = AddressOnBlocksDescription(AddressOnBlocksDescription::HORIZONTAL, i, j);
			BlockDescription blockDescription = field->getBlockDescription(address);
			drawOneBlockDescription(blockDescription);
		}
	}
}

void RowsDescriptionView::drawOneBlockDescription(BlockDescription blockDescription)
{
	//TODO: start drawing from right and check the width of canvas image
	AddressOnBlocksDescription address = blockDescription.getAddress();
	int screenY = static_cast<int>(address.getLine()) * constants.squareSize;
	int screenX = static_cast<int>(address.getCount()) * constants.squareSize;
	
	QPainter painter(&image);
	painter.setPen(QPen(constants.myPenColor, constants.myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	
	// square - mój prostokąt:
	QRect rectangle = QRect(screenX, screenY, constants.squareSize, constants.squareSize);
	painter.fillRect(rectangle, Qt::yellow);
	painter.drawRect(rectangle);
	
	//malowanie tekstu z textBoxa na rysunku:
	QStaticText text = QString::number(blockDescription.getBlockSize());
	QFont font("Times", 14);
	font.setStyleStrategy(QFont::ForceOutline);
	painter.setFont(font);
	const int leftPadding = 1;
	painter.drawStaticText(screenX+leftPadding, screenY, text);
	
	update();
}

void RowsDescriptionView::drawCleanOneBlock(AddressOnBlocksDescription address)
{
	int screenY = static_cast<int>(address.getLine()) * constants.squareSize;
	int screenX = static_cast<int>(address.getCount()) * constants.squareSize;
	
	QPainter painter(&image);
	QColor backgroundColor = Qt::white;
	painter.setPen(QPen(backgroundColor, constants.myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	
	QRect rectangle = QRect(screenX, screenY, constants.squareSize, constants.squareSize);
	painter.fillRect(rectangle, backgroundColor);
	painter.drawRect(rectangle);
	update();
}

void RowsDescriptionView::initTextBox()
{
	qTextEdit = new QTextEdit("0", this);
	qTextEdit->setFixedHeight(constants.squareSize);
	qTextEdit->setFixedWidth(constants.squareSize);
	qTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	qTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	qTextEdit->hide();
}

void RowsDescriptionView::hideTextBox()
{
	qTextEdit->hide();
}

void RowsDescriptionView::saveTextBoxToBlockDescription()
{
	if (! qTextEdit->isHidden())
	{
		size_t count = static_cast<size_t>(qTextEdit->pos().x() / constants.squareSize);
		size_t row = static_cast<size_t>(qTextEdit->pos().y() / constants.squareSize);
		
		AddressOnBlocksDescription address = AddressOnBlocksDescription(AddressOnBlocksDescription::HORIZONTAL, row, count);
		QString textFromBox = qTextEdit->toPlainText();
		size_t blockSize = static_cast<size_t>(textFromBox.toInt());
		BlockDescription blockDecription = BlockDescription(address, blockSize);
		field->updateBlockDescription(blockDecription);
	}
}

void RowsDescriptionView::moveAndShowTextBox(AddressOnBlocksDescription address)
{
	int screenX = static_cast<int>(address.getCount()) * constants.squareSize;
	int screenY = static_cast<int>(address.getLine()) * constants.squareSize;
	qTextEdit->move(screenX, screenY);
	qTextEdit->show();
	qTextEdit->setFocus();
	qTextEdit->selectAll();
}

void RowsDescriptionView::initInsertingButton()
{
	insertingButton = new QPushButton("+", this);
	insertingButton->setFixedHeight(constants.squareSize);
	insertingButton->setFixedWidth(insertingButtonWidth);
	insertingButton->setStatusTip("insert or add new block description");
	setMouseTracking(true);
	connect(insertingButton, &QPushButton::clicked, this, &RowsDescriptionView::onInsertingButtonClick);
	hideInsertingButton();
}

void RowsDescriptionView::hideInsertingButton()
{
	insertingButton->hide();
}

void RowsDescriptionView::moveAndShowInsertingButton(AddressOnBlocksDescription address)
{
	int screenY = static_cast<int>(address.getLine()) * constants.squareSize;
	int screenX = static_cast<int>(address.getCount()) * constants.squareSize - (insertingButtonWidth/2);
	insertingButton->move(screenX, screenY);
	insertingButton->show();
}
