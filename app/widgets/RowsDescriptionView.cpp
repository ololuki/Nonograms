#include "RowsDescriptionView.h"

#include <QPainter>
#include <QRect>
#include <QPaintEvent>
#include <QStaticText>


RowsDescriptionView::RowsDescriptionView(QWidget *parent) : QWidget(parent)
{
	setAttribute(Qt::WA_StaticContents);
	QSize size(211, 211);
	resize(size);
	initTextBox();
	initInsertingButton();
}

void RowsDescriptionView::setField(std::shared_ptr<BlocksDescriptionField> field)
{
	this->field = field;
	connect(static_cast<BlocksDescriptionField*>(this->field.get()), &BlocksDescriptionField::dataChanged, this, &RowsDescriptionView::onDataChanged);
	
	int widthInSquares = 3;
	int screenX = widthInSquares * squareSize + myPenWidth;
	int screenY = static_cast<int>(field->getHeight()) * squareSize + myPenWidth;
	QSize size(screenX, screenY);
	resize(size);
	onDataChanged();
}

void RowsDescriptionView::onDataChanged()
{
	size_t currentWidth = static_cast<size_t>(minimumWidth() / squareSize);
	if (field->rowsDescriptionWidth() > currentWidth)
	{
		int newWidthInSquares = static_cast<int>(field->rowsDescriptionWidth());
		int screenX = newWidthInSquares * squareSize + myPenWidth;
		int screenY = static_cast<int>(field->getHeight()) * squareSize + myPenWidth;
		QSize size(screenX, screenY);
		resize(size);
	}
	redrawAll();
}

void RowsDescriptionView::onInsertingButtonClick()
{
	size_t count = static_cast<size_t>((insertingButton->pos().x() + squareSize) / squareSize);
	size_t row = static_cast<size_t>(insertingButton->pos().y() / squareSize);
	
	AddressOnBlocksDescription address = AddressOnBlocksDescription(AddressOnBlocksDescription::HORIZONTAL, row, count);
	if (count < field->numberOfBlocksInRow(row))
	{
		field->insertDescriptionBefore(BlockDescription(address, 0));
	}
	else if (count == field->numberOfBlocksInRow(row))
	{
		field->addDescriptionAtEnd(BlockDescription(address, 0));
	}
}

void RowsDescriptionView::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QRect dirtyRect = event->rect();
	painter.drawImage(dirtyRect, image, dirtyRect);
}

void RowsDescriptionView::mousePressEvent(QMouseEvent *event)
{
	saveTextBoxToBlockDescription();
	QPoint screenPoint = event->pos();
	if (isPointOnDefinedDescription(screenPoint))
	{
		size_t count = static_cast<size_t>(screenPoint.x() / squareSize);
		size_t row = static_cast<size_t>(screenPoint.y() / squareSize);
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
	int halfSquareSize = squareSize/2;
	size_t line = static_cast<size_t>(screenPoint.y() / squareSize);
	size_t count = static_cast<size_t>((screenPoint.x() + halfSquareSize) / squareSize);
	AddressOnBlocksDescription address(AddressOnBlocksDescription::orientation::HORIZONTAL, line, count);
	if ((screenPoint.x() + insertingButtonWidth/2) % squareSize < insertingButtonWidth)
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
	size_t count = static_cast<size_t>(screenPoint.x() / squareSize);
	size_t line = static_cast<size_t>(screenPoint.y() / squareSize);
	AddressOnBlocksDescription address = AddressOnBlocksDescription(AddressOnBlocksDescription::HORIZONTAL, line, count);
	return (field->isDefinedColumnDescriptionAt(address));
}

void RowsDescriptionView::redrawAll()
{
	for(size_t i = 0; i < field->getHeight(); i++)
	{
		size_t numberOfBlocksInLine = field->numberOfBlocksInRow(i);
		AddressOnBlocksDescription addressAfterLine = AddressOnBlocksDescription(AddressOnBlocksDescription::HORIZONTAL, i, numberOfBlocksInLine);
		drawCleanOneBlock(addressAfterLine);
	}
	for(size_t i = 0; i < field->getHeight(); i++)
	{
		size_t numberOfBlocksInLine = field->numberOfBlocksInRow(i);
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
	int screenY = static_cast<int>(address.getLine()) * squareSize;
	int screenX = static_cast<int>(address.getCount()) * squareSize;
	
	QPainter painter(&image);
	painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	
	// square - mój prostokąt:
	QRect rectangle = QRect(screenX, screenY, squareSize, squareSize);
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
	int screenY = static_cast<int>(address.getLine()) * squareSize;
	int screenX = static_cast<int>(address.getCount()) * squareSize;
	
	QPainter painter(&image);
	QColor backgroundColor = Qt::white;
	painter.setPen(QPen(backgroundColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	
	QRect rectangle = QRect(screenX, screenY, squareSize, squareSize);
	painter.fillRect(rectangle, backgroundColor);
	painter.drawRect(rectangle);
	update();
}

void RowsDescriptionView::initTextBox()
{
	qTextEdit = new QTextEdit("0", this);
	qTextEdit->setFixedHeight(squareSize);
	qTextEdit->setFixedWidth(squareSize);
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
		size_t count = static_cast<size_t>(qTextEdit->pos().x() / squareSize);
		size_t row = static_cast<size_t>(qTextEdit->pos().y() / squareSize);
		
		AddressOnBlocksDescription address = AddressOnBlocksDescription(AddressOnBlocksDescription::HORIZONTAL, row, count);
		QString textFromBox = qTextEdit->toPlainText();
		size_t blockSize = static_cast<size_t>(textFromBox.toInt());
		BlockDescription blockDecription = BlockDescription(address, blockSize);
		field->updateBlockDescription(blockDecription);
	}
}

void RowsDescriptionView::moveAndShowTextBox(AddressOnBlocksDescription address)
{
	int screenX = static_cast<int>(address.getCount()) * squareSize;
	int screenY = static_cast<int>(address.getLine()) * squareSize;
	qTextEdit->move(screenX, screenY);
	qTextEdit->show();
	qTextEdit->setFocus();
	qTextEdit->selectAll();
}

void RowsDescriptionView::initInsertingButton()
{
	insertingButton = new QPushButton("+", this);
	insertingButton->setFixedHeight(squareSize);
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
	int screenY = static_cast<int>(address.getLine()) * squareSize;
	int screenX = static_cast<int>(address.getCount()) * squareSize - (insertingButtonWidth/2);
	insertingButton->move(screenX, screenY);
	insertingButton->show();
}

void RowsDescriptionView::resize(const QSize &newSize)
{
	setMinimumSize(newSize);		// for scroll area, minimum size - you cannot shrink window size lower than this	
	
	// init image:
	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));
	image = newImage;
}
