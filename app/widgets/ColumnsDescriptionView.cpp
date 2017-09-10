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
#include "ColumnsDescriptionView.h"

#include <QPainter>
#include <QRect>
#include <QPaintEvent>
#include <QStaticText>


ColumnsDescriptionView::ColumnsDescriptionView(QWidget *parent)
	: DrawableView(parent)
{
	initTextBox();
	initInsertingButton();
}

void ColumnsDescriptionView::setField(std::shared_ptr<BlocksDescriptionField> field)
{
	this->field = field;
	connect(static_cast<BlocksDescriptionField*>(this->field.get()), &BlocksDescriptionField::blocksDescriptionChanged, this, &ColumnsDescriptionView::onDataChanged);
	
	int screenX = static_cast<int>(this->field->getNumberOfLines()) * constants.squareSize + constants.myPenWidth;
	int heightInSquares = 3;
	int screenY = heightInSquares * constants.squareSize + constants.myPenWidth;
	QSize size(screenX, screenY);
	resize(size);
	onDataChanged();
}

void ColumnsDescriptionView::onDataChanged()
{
	size_t currentHeight = static_cast<size_t>(minimumHeight() / constants.squareSize);
	if (field->allBlocksDescriptionLength() > currentHeight)
	{
		int screenX = static_cast<int>(field->getNumberOfLines()) * constants.squareSize + constants.myPenWidth;
		int newHeightInSquares = static_cast<int>(field->allBlocksDescriptionLength());
		int screenY = newHeightInSquares * constants.squareSize + constants.myPenWidth;
		QSize size(screenX, screenY);
		resize(size);
	}
	redrawAll();
}

///
/// \brief	invoke when one block description is changed
/// \param	address lying on edited (changed) line of blocks descriptions
///
void ColumnsDescriptionView::onLineDescriptionChanged(AddressOnBlocksDescription address)
{
	
}

///
/// \brief	turning on visibility of inserting (+) button between block descriptions.
///			Plus button is visible until cursor is gone out of area of plus button.
/// \param	address of block description after plus button position.
///			Plus button will be inserted between this and previous address.
///
void ColumnsDescriptionView::showInsertingButtonBefore(AddressOnBlocksDescription address)
{
	if (address.isColumn())
	{
		moveAndShowInsertingButton(address);
	}
}

void ColumnsDescriptionView::showDescriptionEditingBox(AddressOnBlocksDescription address)
{
	
}

void ColumnsDescriptionView::onInsertingButtonClick()
{
	size_t column = static_cast<size_t>(insertingButton->pos().x() / constants.squareSize);
	size_t count = static_cast<size_t>((insertingButton->pos().y() + constants.squareSize) / constants.squareSize);
	
	AddressOnBlocksDescription address = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, column, count);
	//TODO emit onInsertingButtonClick(Qt::MouseButton, address);
	if (count < field->numberOfBlocksInLine(column))
	{
		field->insertDescriptionBefore(BlockDescription(address, 0));
	}
	else if (count == field->numberOfBlocksInLine(column))
	{
		field->addDescriptionAtEnd(BlockDescription(address, 0));
	}
}

void ColumnsDescriptionView::mousePressEvent(QMouseEvent *event)
{
	saveTextBoxToBlockDescription();
	QPoint screenPoint = event->pos();
	if (isPointOnDefinedDescription(screenPoint))
	{
		size_t squareX = static_cast<size_t>(screenPoint.x() / constants.squareSize);
		size_t squareY = static_cast<size_t>(screenPoint.y() / constants.squareSize);
		AddressOnBlocksDescription address(AddressOnBlocksDescription::orientation::VERTICAL, squareX, squareY);
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

void ColumnsDescriptionView::mouseMoveEvent(QMouseEvent *event)
{
	QPoint screenPoint = event->pos();
	int halfSquareSize = constants.squareSize/2;
	size_t squareX = static_cast<size_t>(screenPoint.x() / constants.squareSize);
	size_t squareY = static_cast<size_t>((screenPoint.y() + halfSquareSize) / constants.squareSize);
	AddressOnBlocksDescription address(AddressOnBlocksDescription::orientation::VERTICAL, squareX, squareY);
	if ((screenPoint.y() + insertingButtonHeight/2) % constants.squareSize < insertingButtonHeight)
	{
		screenPoint.setY(screenPoint.y() - insertingButtonHeight/2);	// remap to area with defined descriptions + area for half of insertButtons
		if(isPointOnDefinedDescription(screenPoint))
		{
			insertingButtonHover(address);
		} else {
			hideInsertingButton();
		}
	} else {
		hideInsertingButton();
	}
}

bool ColumnsDescriptionView::isPointOnDefinedDescription(QPoint screenPoint)
{
	size_t line = static_cast<size_t>(screenPoint.x() / constants.squareSize);
	size_t count = static_cast<size_t>(screenPoint.y() / constants.squareSize);
	AddressOnBlocksDescription address = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, line, count);
	return (field->isDefinedDescriptionAt(address));
}

void ColumnsDescriptionView::redrawAll()
{
	for(size_t i = 0; i < field->getNumberOfLines(); i++)
	{
		size_t numberOfBlocksInLine = field->numberOfBlocksInLine(i);
		AddressOnBlocksDescription addressAfterLine = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, i, numberOfBlocksInLine);
		drawCleanOneBlock(addressAfterLine);
	}
	for(size_t i = 0; i < field->getNumberOfLines(); i++)
	{
		size_t numberOfBlocksInLine = field->numberOfBlocksInLine(i);
		for(size_t j = 0; j < numberOfBlocksInLine; j++)
		{
			AddressOnBlocksDescription address = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, i, j);
			BlockDescription blockDescription = field->getBlockDescription(address);
			drawOneBlockDescription(blockDescription);
		}
	}
}

void ColumnsDescriptionView::drawOneBlockDescription(BlockDescription blockDescription)
{
	//TODO: start drawing from bottom and check the height of canvas image
	AddressOnBlocksDescription address = blockDescription.getAddress();
	int screenX = static_cast<int>(address.getLine()) * constants.squareSize;
	int screenY = static_cast<int>(address.getCount()) * constants.squareSize;
	
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

void ColumnsDescriptionView::drawCleanOneBlock(AddressOnBlocksDescription address)
{
	int screenX = static_cast<int>(address.getLine()) * constants.squareSize;
	int screenY = static_cast<int>(address.getCount()) * constants.squareSize;
	
	QPainter painter(&image);
	QColor backgroundColor = Qt::white;
	painter.setPen(QPen(backgroundColor, constants.myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	
	QRect rectangle = QRect(screenX, screenY, constants.squareSize, constants.squareSize);
	painter.fillRect(rectangle, backgroundColor);
	painter.drawRect(rectangle);
	update();
}

void ColumnsDescriptionView::initTextBox()
{
	qTextEdit = new QTextEdit("0", this);
	qTextEdit->setFixedHeight(constants.squareSize);
	qTextEdit->setFixedWidth(constants.squareSize);
	qTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	qTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	qTextEdit->hide();
}

void ColumnsDescriptionView::hideTextBox()
{
	qTextEdit->hide();
}

void ColumnsDescriptionView::saveTextBoxToBlockDescription()
{
	if (! qTextEdit->isHidden())
	{
		size_t squareX = static_cast<size_t>(qTextEdit->pos().x() / constants.squareSize);
		size_t squareY = static_cast<size_t>(qTextEdit->pos().y() / constants.squareSize);
		
		AddressOnBlocksDescription address = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, squareX, squareY);
		QString textFromBox = qTextEdit->toPlainText();
		size_t blockSize = static_cast<size_t>(textFromBox.toInt());
		BlockDescription blockDecription = BlockDescription(address, blockSize);
		field->updateBlockDescription(blockDecription);
	}
}

void ColumnsDescriptionView::moveAndShowTextBox(AddressOnBlocksDescription address)
{
	int screenX = static_cast<int>(address.getLine()) * constants.squareSize;
	int screenY = static_cast<int>(address.getCount()) * constants.squareSize;
	qTextEdit->move(screenX, screenY);
	qTextEdit->show();
	qTextEdit->setFocus();
	qTextEdit->selectAll();
}

void ColumnsDescriptionView::initInsertingButton()
{
	insertingButton = new QPushButton("+", this);
	insertingButton->setFixedHeight(insertingButtonHeight);
	insertingButton->setFixedWidth(constants.squareSize);
	insertingButton->setStatusTip("insert or add new block description");
	setMouseTracking(true);
	connect(insertingButton, &QPushButton::clicked, this, &ColumnsDescriptionView::onInsertingButtonClick);
	hideInsertingButton();
}

void ColumnsDescriptionView::hideInsertingButton()
{
	insertingButton->hide();
}

void ColumnsDescriptionView::moveAndShowInsertingButton(AddressOnBlocksDescription address)
{
	int screenX = static_cast<int>(address.getLine()) * constants.squareSize;
	int screenY = static_cast<int>(address.getCount()) * constants.squareSize - (constants.squareSize/4);
	insertingButton->move(screenX, screenY);
	insertingButton->show();
}
