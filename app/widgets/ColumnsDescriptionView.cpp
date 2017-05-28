#include "ColumnsDescriptionView.h"

#include <QPainter>
#include <QRect>
#include <QPaintEvent>
#include <QStaticText>
#include <string>


ColumnsDescriptionView::ColumnsDescriptionView(QWidget *parent) : QWidget(parent)
{
	setAttribute(Qt::WA_StaticContents);
	QSize size(211, 211);
	resize(size);
	initTextBox();
	initInsertingButton();
	
}

void ColumnsDescriptionView::setField(BlocksDescriptionField *field)
{
	this->field = field;
	connect(field, &BlocksDescriptionField::dataChanged, this, &ColumnsDescriptionView::onDataChanged);
	
	int screenX = static_cast<int>(field->getWidth()) * squareSize + myPenWidth;
	int heightInSquares = 3;
	int screenY = heightInSquares * squareSize + myPenWidth;
	QSize size(screenX, screenY);
	resize(size);
	onDataChanged();
}

void ColumnsDescriptionView::onDataChanged()
{
	size_t currentHeight = static_cast<size_t>(minimumHeight() / squareSize);
	if (field->columnsDescriptionHeight() > currentHeight)
	{
		int screenX = static_cast<int>(field->getWidth()) * squareSize + myPenWidth;
		int newHeightInSquares = static_cast<int>(field->columnsDescriptionHeight());
		int screenY = newHeightInSquares * squareSize + myPenWidth;
		QSize size(screenX, screenY);
		resize(size);
	}
	redrawAll();
}

void ColumnsDescriptionView::onInsertingButtonClick()
{
	size_t column = static_cast<size_t>(insertingButton->pos().x() / squareSize);
	size_t count = static_cast<size_t>((insertingButton->pos().y() + squareSize) / squareSize);
	
	AddressOnBlocksDescription address = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, column, count);
	if (count < field->numberOfBlocksInColumn(column))
	{
		field->insertDescriptionBefore(BlockDescription(address, 0));
	}
	else if (count == field->numberOfBlocksInColumn(column))
	{
		field->addDescriptionAtEnd(BlockDescription(address, 0));
	}
}

void ColumnsDescriptionView::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QRect dirtyRect = event->rect();
	painter.drawImage(dirtyRect, image, dirtyRect);
}

void ColumnsDescriptionView::mousePressEvent(QMouseEvent *event)
{
	saveTextBoxToBlockDescription();
	QPoint screenPoint = event->pos();
	if (isPointOnDefinedDescription(screenPoint))
	{
		size_t squareX = static_cast<size_t>(screenPoint.x() / squareSize);
		size_t squareY = static_cast<size_t>(screenPoint.y() / squareSize);
		AddressOnBlocksDescription address(AddressOnBlocksDescription::orientation::VERTICAL, squareX, squareY);
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
	size_t squareX = static_cast<size_t>(screenPoint.x() / squareSize);
	size_t squareY = static_cast<size_t>((screenPoint.y() + (squareSize/2)) / squareSize);
	AddressOnBlocksDescription address(AddressOnBlocksDescription::orientation::VERTICAL, squareX, squareY);
	moveAndShowInsertingButton(address);
}

bool ColumnsDescriptionView::isPointOnDefinedDescription(QPoint screenPoint)
{
	size_t squareX = static_cast<size_t>(screenPoint.x() / squareSize);
	size_t squareY = static_cast<size_t>(screenPoint.y() / squareSize);
	return (field->isDefinedColumnDescriptionAt(squareX, squareY));
}

void ColumnsDescriptionView::redrawAll()
{
	for(size_t i = 0; i < field->getWidth(); i++)
	{
		size_t numberOfBlocksInLine = field->numberOfBlocksInColumn(i);
		AddressOnBlocksDescription addressAfterLine = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, i, numberOfBlocksInLine);
		drawCleanOneBlock(addressAfterLine);
	}
	for(size_t i = 0; i < field->getWidth(); i++)
	{
		size_t numberOfBlocksInLine = field->numberOfBlocksInColumn(i);
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
	int screenX = static_cast<int>(address.getLine()) * squareSize;
	int screenY = static_cast<int>(address.getCount()) * squareSize;
	
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

void ColumnsDescriptionView::drawCleanOneBlock(AddressOnBlocksDescription address)
{
	int screenX = static_cast<int>(address.getLine()) * squareSize;
	int screenY = static_cast<int>(address.getCount()) * squareSize;
	
	QPainter painter(&image);
	QColor backgroundColor = Qt::white;
	painter.setPen(QPen(backgroundColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	
	QRect rectangle = QRect(screenX, screenY, squareSize, squareSize);
	painter.fillRect(rectangle, backgroundColor);
	painter.drawRect(rectangle);
	update();
}

void ColumnsDescriptionView::initTextBox()
{
	qTextEdit = new QTextEdit("0", this);
	qTextEdit->setFixedHeight(30);
	qTextEdit->setFixedWidth(30);
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
		size_t squareX = static_cast<size_t>(qTextEdit->pos().x() / squareSize);
		size_t squareY = static_cast<size_t>(qTextEdit->pos().y() / squareSize);
		
		AddressOnBlocksDescription address = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, squareX, squareY);
		QString textFromBox = qTextEdit->toPlainText();
		size_t blockSize = static_cast<size_t>(textFromBox.toInt());
		BlockDescription blockDecription = BlockDescription(address, blockSize);
		field->updateBlockDescription(blockDecription);
	}
}

void ColumnsDescriptionView::moveAndShowTextBox(AddressOnBlocksDescription address)
{
	int screenX = static_cast<int>(address.getLine()) * squareSize;
	int screenY = static_cast<int>(address.getCount()) * squareSize;
	qTextEdit->move(screenX, screenY);
	qTextEdit->show();
	qTextEdit->setFocus();
	qTextEdit->selectAll();
}

void ColumnsDescriptionView::initInsertingButton()
{
	insertingButton = new QPushButton("+", this);
	insertingButton->setFixedHeight(squareSize/2);
	insertingButton->setFixedWidth(squareSize);
	insertingButton->setStatusTip("insert or add new block description");
	setMouseTracking(true);
	connect(insertingButton, &QPushButton::clicked, this, &ColumnsDescriptionView::onInsertingButtonClick);
}

void ColumnsDescriptionView::hideInsertingButton()
{
	insertingButton->hide();
}

void ColumnsDescriptionView::moveAndShowInsertingButton(AddressOnBlocksDescription address)
{
	int screenX = static_cast<int>(address.getLine()) * squareSize;
	int screenY = static_cast<int>(address.getCount()) * squareSize - (squareSize/4);
	insertingButton->move(screenX, screenY);
	insertingButton->show();
}

void ColumnsDescriptionView::resize(const QSize &newSize)
{
	setMinimumSize(newSize);		// for scroll area, minimum size - you cannot shrink window size lower than this	
	
	// init image:
	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));
	image = newImage;
}
