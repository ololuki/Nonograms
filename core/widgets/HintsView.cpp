/**********************************************************************
 * Copyright (C) 2017 - 2019 Ololuki
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

void HintsView::setField(const std::shared_ptr<const HintsFieldModel> &field)
{
	this->field = field;
	orientation = this->field->getOrientation();
	connect(
		static_cast<const HintsFieldModel*>(this->field.get()),
		&HintsFieldModel::lineOfHintsChanged,
		this,
		&HintsView::onLineOfHintsChanged
	);

	connect(static_cast<const HintsFieldModel*>(this->field.get()),
	        &HintsFieldModel::hintsChanged,
	        this,
	        &HintsView::onHintsChanged);
	
	QSize size = calculateSize();
	resize(size);
	initInsertingButton();
	redrawAll();
}

///
/// \brief Invoked when hint or hints in line changed.
/// Invoked by model to inform about changes.
/// \param lineNumber - number (address) of changed line
/// \param orientation - orientation (address) of changed line
///
void HintsView::onLineOfHintsChanged(int lineNumber, Orientation orientation)
{
	// TODO: Redraw only one line
	onHintsChanged();
}

void HintsView::onHintsChanged()
{
	QSize size = calculateSize();
	resize(size);
	redrawAll();
}

///
/// \brief	turning on visibility of inserting (+) button between block descriptions.
///			Plus button is visible until cursor is gone out of area of plus button.
/// \param	address of block description after plus button position.
///			Plus button will be inserted between this and previous address.
///
void HintsView::onShowInsertingButtonBefore(AddressOfHint address)
{
	moveAndShowInsertingButton(address);
}

void HintsView::onShowHintEditingBox(AddressOfHint address)
{
	moveAndShowTextBox(address);
}

void HintsView::onInsertingButtonClick()
{
	int line;
	int count;
	if (orientation == Orientation::VERTICAL)
	{
		line = insertingButton->pos().x() / constants.squareSize;
		count = (insertingButton->pos().y() + constants.squareSize) / constants.squareSize;
	} else {
		line = insertingButton->pos().y() / constants.squareSize;
		count = (insertingButton->pos().x() + constants.squareSize) / constants.squareSize;
	}
	AddressOfHint address = AddressOfHint(orientation, line, count);
	emit action(HintAction::HintInsertBefore, address);
}

void HintsView::mousePressEvent(QMouseEvent *event)
{
	saveTextBoxToHint();
	QPoint screenPoint = event->pos();
	if (isPointOnDefinedHint(screenPoint))
	{
		int hintLine;
		int hintCount;
		if (orientation == Orientation::VERTICAL)
		{
			hintLine = screenPoint.x() / constants.squareSize;
			hintCount = screenPoint.y() / constants.squareSize;
		} else {
			hintLine = screenPoint.y() / constants.squareSize;
			hintCount = screenPoint.x() / constants.squareSize;
		}
		
		AddressOfHint address(orientation, hintLine, hintCount);
		
		if (event->button() == Qt::LeftButton)
		{
			action(HintAction::ShowEditBox , address);
		}
		else if (event->button() == Qt::RightButton)
		{
			hideTextBox();
			action(HintAction::HintDelete, address);
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
	if(orientation == Orientation::VERTICAL)
	{
		hintLine = screenPoint.x() / constants.squareSize;
		hintCount = (screenPoint.y() + halfSquareSize) / constants.squareSize;
	} else {
		hintLine = screenPoint.y() / constants.squareSize;
		hintCount = (screenPoint.x() + halfSquareSize) / constants.squareSize;
	}
	
	AddressOfHint address(orientation, hintLine, hintCount);
	if(orientation == Orientation::VERTICAL)
	{
		if ((screenPoint.y() + insertingButtonHeight/2) % constants.squareSize < insertingButtonHeight)
		{
			screenPoint.setY(screenPoint.y() - insertingButtonHeight/2);	// remap to area with defined descriptions + area for half of insertButtons
			if (screenPoint.y() < 0) screenPoint.setY(0);
			if(isPointOnDefinedHint(screenPoint))
			{
				action(HintAction::InsertingButtonHover, address);
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
			if(isPointOnDefinedHint(screenPoint))
				moveAndShowInsertingButton(address);
			else
				hideInsertingButton();
		} else {
			hideInsertingButton();
		}
	}
}

bool HintsView::isPointOnDefinedHint(QPoint screenPoint)
{
	int line;
	int count;
	if(orientation == Orientation::VERTICAL)
	{
		line = screenPoint.x() / constants.squareSize;
		count = screenPoint.y() / constants.squareSize;
	} else {
		line = screenPoint.y() / constants.squareSize;
		count = screenPoint.x() / constants.squareSize;
	}
	AddressOfHint address = AddressOfHint(orientation, line, count);
	return (field->isDefinedHintAt(address));
}

void HintsView::redrawAll()
{
	for(int i = 0; i < field->getNumberOfLines(); i++)
	{
		int numberOfBlocksInLine = field->numberOfBlocksInLine(i);
		AddressOfHint addressAfterLine = AddressOfHint(orientation, i, numberOfBlocksInLine);
		undrawOneHint(addressAfterLine);
	}
	for(int i = 0; i < field->getNumberOfLines(); i++)
	{
		int numberOfBlocksInLine = field->numberOfBlocksInLine(i);
		for(int j = 0; j < numberOfBlocksInLine; j++)
		{
			AddressOfHint address = AddressOfHint(orientation, i, j);
			Hint hint = field->getHint(address);
			drawOneHint(hint);
		}
	}
}

void HintsView::drawOneHint(Hint hint)
{
	//TODO: start drawing from bottom and check the height of canvas image
	AddressOfHint address = hint.getAddress();
	int screenX;
	int screenY;
	if (orientation == Orientation::VERTICAL)
	{
		screenX = address.getLine() * constants.squareSize;
		screenY = address.getCount() * constants.squareSize;
	} else {
		screenX = address.getCount() * constants.squareSize;
		screenY = address.getLine() * constants.squareSize;
	}
	QPainter painter(&image);
	painter.setPen(QPen(constants.myPenColor, constants.myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	
	// square - mój prostokąt:
	QRect rectangle;
	rectangle = QRect(screenX, screenY, constants.squareSize, constants.squareSize);
	painter.fillRect(rectangle, Qt::yellow);
	painter.drawRect(rectangle);
	
	//malowanie tekstu z textBoxa na rysunku:
	QStaticText text = QStaticText(QString::number(hint.getBlockSize()));
	QFont font("Times", 14);
	font.setStyleStrategy(QFont::ForceOutline);
	painter.setFont(font);
	const int leftPadding = 1;
	painter.drawStaticText(screenX+leftPadding, screenY, text);
	
	update();
}

/// Draws white square in place of Hint. It clears all borders.
void HintsView::undrawOneHint(AddressOfHint address)
{
	int screenX;
	int screenY;
	if(orientation == Orientation::VERTICAL)
	{
		screenX = address.getLine() * constants.squareSize;
		screenY = address.getCount() * constants.squareSize;
	} else {
		screenX = address.getCount() * constants.squareSize;
		screenY = address.getLine() * constants.squareSize;
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

void HintsView::saveTextBoxToHint()
{
	if (! qTextEdit->isHidden())
	{
		int line;
		int count;
		if (orientation == Orientation::VERTICAL)
		{
			line = qTextEdit->pos().x() / constants.squareSize;
			count = qTextEdit->pos().y() / constants.squareSize;
		} else {
			line = qTextEdit->pos().y() / constants.squareSize;
			count = qTextEdit->pos().x() / constants.squareSize;
		}
		AddressOfHint address = AddressOfHint(orientation, line, count);
		QString textFromBox = qTextEdit->toPlainText();
		int blockSize = textFromBox.toInt();
		Hint hint = Hint(address, blockSize);
		emit action(HintAction::HintUpdate, hint);
	}
}

void HintsView::moveAndShowTextBox(AddressOfHint address)
{
	int screenX;
	int screenY;
	if (orientation == Orientation::VERTICAL)
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
	insertingButton->installEventFilter(&insertingButtonEventFilter);
	if(orientation == Orientation::VERTICAL)
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

void HintsView::moveAndShowInsertingButton(AddressOfHint address)
{
	int screenX;
	int screenY;
	if (orientation == Orientation::VERTICAL)
	{
		screenX = address.getLine() * constants.squareSize;
		screenY = address.getCount() * constants.squareSize - (insertingButtonHeight/2);
	} else {
		screenX = address.getCount() * constants.squareSize - (insertingButtonHeight/2);
		screenY = address.getLine() * constants.squareSize;
	}
	insertingButton->move(screenX, screenY);
	insertingButton->show();
}

///
/// \brief Calculate size of screen in pixels.
/// \return current size of screen in pixels as QSize.
///
QSize HintsView::calculateSize()
{
	int additionalLengthInSquares = 1;
	int screenX;
	int screenY;
	if (orientation == Orientation::VERTICAL)
	{
		screenX = field->getNumberOfLines() * constants.squareSize + constants.myPenWidth;
		int newHeightInSquares = field->allHintsLength() + additionalLengthInSquares;
		screenY = newHeightInSquares * constants.squareSize + constants.myPenWidth;
	} else {
		int newWidthInSquares = field->allHintsLength() + additionalLengthInSquares;
		screenX = newWidthInSquares * constants.squareSize + constants.myPenWidth;
		screenY = field->getNumberOfLines() * constants.squareSize + constants.myPenWidth;
	}
	return QSize(screenX, screenY);
}
