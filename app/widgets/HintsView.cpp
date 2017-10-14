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
#include "HintsView.h"

#include <QPainter>
#include <QRect>
#include <QPaintEvent>
#include <QStaticText>


HintsView::HintsView(QWidget *parent)
	: DrawableView(parent)
{
	initTextBox();
	initInsertingButton();
}

void HintsView::setField(std::shared_ptr<BlocksDescriptionField> field)
{
	this->field = field;
	orientation = field->getOrientation();
	connect(static_cast<BlocksDescriptionField*>(this->field.get()), &BlocksDescriptionField::blocksDescriptionChanged, this, &HintsView::onDataChanged);
	
	int initialLengthInSquares = 3;
	int screenX;
	int screenY;
	if (orientation == AddressOnBlocksDescription::VERTICAL)
	{
		screenX = static_cast<int>(this->field->getNumberOfLines()) * constants.squareSize + constants.myPenWidth;
		screenY = initialLengthInSquares * constants.squareSize + constants.myPenWidth;
	} else {
		screenX = initialLengthInSquares * constants.squareSize + constants.myPenWidth;
		screenY = static_cast<int>(this->field->getNumberOfLines()) * constants.squareSize + constants.myPenWidth;
	}
	
	QSize size(screenX, screenY);
	resize(size);
	initInsertingButton();
	onDataChanged();
}

void HintsView::onDataChanged()
{
	if (orientation == AddressOnBlocksDescription::VERTICAL)
	{
		int currentHeight = minimumHeight() / constants.squareSize;
		if (field->allBlocksDescriptionLength() > currentHeight)
		{
			int screenX = field->getNumberOfLines() * constants.squareSize + constants.myPenWidth;
			int newHeightInSquares = static_cast<int>(field->allBlocksDescriptionLength());
			int screenY = newHeightInSquares * constants.squareSize + constants.myPenWidth;
			QSize size(screenX, screenY);
			resize(size);
		}
	} else {
		int currentWidth = minimumWidth() / constants.squareSize;
		if (field->allBlocksDescriptionLength() > currentWidth)
		{
			int newWidthInSquares = static_cast<int>(field->allBlocksDescriptionLength());
			int screenX = newWidthInSquares * constants.squareSize + constants.myPenWidth;
			int screenY = static_cast<int>(field->getNumberOfLines()) * constants.squareSize + constants.myPenWidth;
			QSize size(screenX, screenY);
			resize(size);
		}
	}
	redrawAll();
}

///
/// \brief	invoke when one block description is changed
/// \param	address lying on edited (changed) line of blocks descriptions
///
void HintsView::onLineOfHintsChanged(AddressOnBlocksDescription address)
{
	
}

///
/// \brief	turning on visibility of inserting (+) button between block descriptions.
///			Plus button is visible until cursor is gone out of area of plus button.
/// \param	address of block description after plus button position.
///			Plus button will be inserted between this and previous address.
///
void HintsView::showInsertingButtonBefore(AddressOnBlocksDescription address)
{
	moveAndShowInsertingButton(address);
}

void HintsView::showDescriptionEditingBox(AddressOnBlocksDescription address)
{
	
}

void HintsView::onInsertingButtonClick()
{
	int line;
	int count;
	if (orientation == AddressOnBlocksDescription::VERTICAL)
	{
		line = insertingButton->pos().x() / constants.squareSize;
		count = (insertingButton->pos().y() + constants.squareSize) / constants.squareSize;
	} else {
		line = insertingButton->pos().y() / constants.squareSize;
		count = (insertingButton->pos().x() + constants.squareSize) / constants.squareSize;
	}
	AddressOnBlocksDescription address = AddressOnBlocksDescription(orientation, line, count);
	//TODO emit onInsertingButtonClick(Qt::MouseButton, address);
	if (count < field->numberOfBlocksInLine(line))
	{
		field->insertDescriptionBefore(BlockDescription(address, 0));
	}
	else if (count == field->numberOfBlocksInLine(line))
	{
		field->addDescriptionAtEnd(BlockDescription(address, 0));
	}
}

void HintsView::mousePressEvent(QMouseEvent *event)
{
	saveTextBoxToBlockDescription();
	QPoint screenPoint = event->pos();
	if (isPointOnDefinedDescription(screenPoint))
	{
		int hintLine;
		int hintCount;
		if (orientation == AddressOnBlocksDescription::VERTICAL)
		{
			hintLine = screenPoint.x() / constants.squareSize;
			hintCount = screenPoint.y() / constants.squareSize;
		} else {
			hintLine = screenPoint.y() / constants.squareSize;
			hintCount = screenPoint.x() / constants.squareSize;
		}
		
		AddressOnBlocksDescription address(orientation, hintLine, hintCount);
		
		//TODO emit mouseClickedOnBlockDescription(Qt::MouseButton, address);
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

void HintsView::mouseMoveEvent(QMouseEvent *event)
{
	QPoint screenPoint = event->pos();
	int halfSquareSize = constants.squareSize/2;
	int hintLine;
	int hintCount;
	if(orientation == AddressOnBlocksDescription::VERTICAL)
	{
		hintLine = screenPoint.x() / constants.squareSize;
		hintCount = (screenPoint.y() + halfSquareSize) / constants.squareSize;
	} else {
		hintLine = screenPoint.y() / constants.squareSize;
		hintCount = (screenPoint.x() + halfSquareSize) / constants.squareSize;
	}
	
	AddressOnBlocksDescription address(orientation, hintLine, hintCount);
	if(orientation == AddressOnBlocksDescription::VERTICAL)
	{
		if ((screenPoint.y() + insertingButtonHeight/2) % constants.squareSize < insertingButtonHeight)
		{
			screenPoint.setY(screenPoint.y() - insertingButtonHeight/2);	// remap to area with defined descriptions + area for half of insertButtons
			if (screenPoint.y() < 0) screenPoint.setY(0);
			if(isPointOnDefinedDescription(screenPoint))
			{
				insertingButtonHover(address);
			} else {
				hideInsertingButton();
			}
		} else {
			hideInsertingButton();
		}
	} else {
		if ((screenPoint.x() + insertingButtonHeight/2) % constants.squareSize < insertingButtonHeight)
		{
			screenPoint.setX(screenPoint.x() - insertingButtonHeight/2);	// remap to area with defined descriptions + area for half of insertButtons
			if (screenPoint.x() < 0) screenPoint.setX(0);
			if(isPointOnDefinedDescription(screenPoint))
				moveAndShowInsertingButton(address);
			else
				hideInsertingButton();
		} else {
			hideInsertingButton();
		}
	}
}

bool HintsView::isPointOnDefinedDescription(QPoint screenPoint)
{
	int line;
	int count;
	if(orientation == AddressOnBlocksDescription::VERTICAL)
	{
		line = screenPoint.x() / constants.squareSize;
		count = screenPoint.y() / constants.squareSize;
	} else {
		line = screenPoint.y() / constants.squareSize;
		count = screenPoint.x() / constants.squareSize;
	}
	AddressOnBlocksDescription address = AddressOnBlocksDescription(orientation, line, count);
	return (field->isDefinedDescriptionAt(address));
}

void HintsView::redrawAll()
{
	for(int i = 0; i < field->getNumberOfLines(); i++)
	{
		int numberOfBlocksInLine = field->numberOfBlocksInLine(i);
		AddressOnBlocksDescription addressAfterLine = AddressOnBlocksDescription(orientation, i, numberOfBlocksInLine);
		drawCleanOneBlock(addressAfterLine);
	}
	for(int i = 0; i < field->getNumberOfLines(); i++)
	{
		int numberOfBlocksInLine = field->numberOfBlocksInLine(i);
		for(int j = 0; j < numberOfBlocksInLine; j++)
		{
			AddressOnBlocksDescription address = AddressOnBlocksDescription(orientation, i, j);
			BlockDescription blockDescription = field->getBlockDescription(address);
			drawOneBlockDescription(blockDescription);
		}
	}
}

void HintsView::drawOneBlockDescription(BlockDescription blockDescription)
{
	//TODO: start drawing from bottom and check the height of canvas image
	AddressOnBlocksDescription address = blockDescription.getAddress();
	int screenX;
	int screenY;
	if (orientation == AddressOnBlocksDescription::VERTICAL)
	{
		screenX = static_cast<int>(address.getLine()) * constants.squareSize;
		screenY = static_cast<int>(address.getCount()) * constants.squareSize;
	} else {
		screenX = static_cast<int>(address.getCount()) * constants.squareSize;
		screenY = static_cast<int>(address.getLine()) * constants.squareSize;
	}
	QPainter painter(&image);
	painter.setPen(QPen(constants.myPenColor, constants.myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	
	// square - mój prostokąt:
	QRect rectangle;
	rectangle = QRect(screenX, screenY, constants.squareSize, constants.squareSize);
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
// todo tu skończyłem
void HintsView::drawCleanOneBlock(AddressOnBlocksDescription address)
{
	int screenX;
	int screenY;
	if(orientation == AddressOnBlocksDescription::VERTICAL)
	{
		screenX = static_cast<int>(address.getLine()) * constants.squareSize;
		screenY = static_cast<int>(address.getCount()) * constants.squareSize;
	} else {
		screenX = static_cast<int>(address.getCount()) * constants.squareSize;
		screenY = static_cast<int>(address.getLine()) * constants.squareSize;
	}
	QPainter painter(&image);
	QColor backgroundColor = Qt::white;
	painter.setPen(QPen(backgroundColor, constants.myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	
	QRect rectangle = QRect(screenX, screenY, constants.squareSize, constants.squareSize);
	painter.fillRect(rectangle, backgroundColor);
	painter.drawRect(rectangle);
	update();
}

void HintsView::initTextBox()
{
	qTextEdit = new QTextEdit("0", this);
	qTextEdit->setFixedWidth(constants.squareSize);
	qTextEdit->setFixedHeight(constants.squareSize);
	qTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	qTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	qTextEdit->hide();
}

void HintsView::hideTextBox()
{
	qTextEdit->hide();
}

void HintsView::saveTextBoxToBlockDescription()
{
	if (! qTextEdit->isHidden())
	{
		int line;
		int count;
		if (orientation == AddressOnBlocksDescription::VERTICAL)
		{
			line = qTextEdit->pos().x() / constants.squareSize;
			count = qTextEdit->pos().y() / constants.squareSize;
		} else {
			line = qTextEdit->pos().y() / constants.squareSize;
			count = qTextEdit->pos().x() / constants.squareSize;
		}
		AddressOnBlocksDescription address = AddressOnBlocksDescription(orientation, line, count);
		QString textFromBox = qTextEdit->toPlainText();
		int blockSize = textFromBox.toInt();
		BlockDescription blockDecription = BlockDescription(address, blockSize);
		field->updateBlockDescription(blockDecription);
	}
}

void HintsView::moveAndShowTextBox(AddressOnBlocksDescription address)
{
	int screenX;
	int screenY;
	if (orientation == AddressOnBlocksDescription::VERTICAL)
	{
		screenX = address.getLine() * constants.squareSize;
		screenY = address.getCount() * constants.squareSize;
	} else {
		screenX = address.getCount() * constants.squareSize;
		screenY = address.getLine() * constants.squareSize;
	}
	qTextEdit->move(screenX, screenY);
	qTextEdit->show();
	qTextEdit->setFocus();
	qTextEdit->selectAll();
}

void HintsView::initInsertingButton()
{
	insertingButton = std::make_shared<QPushButton>("+", this);
	if(orientation == AddressOnBlocksDescription::VERTICAL)
	{
		insertingButton->setFixedWidth(constants.squareSize);
		insertingButton->setFixedHeight(insertingButtonHeight);
	} else {
		insertingButton->setFixedWidth(insertingButtonHeight);
		insertingButton->setFixedHeight(constants.squareSize);
	}
	insertingButton->setStatusTip("insert or add new block description");
	setMouseTracking(true);
	connect
	(
		static_cast<const QPushButton*>(insertingButton.get()),
		&QPushButton::clicked,
		this,
		&HintsView::onInsertingButtonClick
	);
	hideInsertingButton();
}

void HintsView::hideInsertingButton()
{
	insertingButton->hide();
}

void HintsView::moveAndShowInsertingButton(AddressOnBlocksDescription address)
{
	int screenX;
	int screenY;
	if (orientation == AddressOnBlocksDescription::VERTICAL)
	{
		screenX = static_cast<int>(address.getLine()) * constants.squareSize;
		screenY = static_cast<int>(address.getCount()) * constants.squareSize - (insertingButtonHeight/2);
	} else {
		screenX = static_cast<int>(address.getCount()) * constants.squareSize - (insertingButtonHeight/2);
		screenY = static_cast<int>(address.getLine()) * constants.squareSize;
	}
	insertingButton->move(screenX, screenY);
	insertingButton->show();
}
