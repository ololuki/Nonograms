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
}

void ColumnsDescriptionView::setField(BlocksDescriptionField *field)
{
	this->field = field;
	connect(field, &BlocksDescriptionField::dataChanged, this, &ColumnsDescriptionView::onDataChanged);
	
	int screenX = field->getWidth() * squareSize + myPenWidth;
	int heightInSquares = 2;
	int screenY = heightInSquares * squareSize + myPenWidth;
	QSize size(screenX, screenY);
	resize(size);
	onDataChanged();
}

void ColumnsDescriptionView::onDataChanged()
{
	//TODO: if (size() > currentSize) resize(currentSize)
	redrawAll();
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
		if (event->button() == Qt::LeftButton) {
			size_t squareX = static_cast<size_t>(screenPoint.x()) / squareSize;
			size_t squareY = static_cast<size_t>(screenPoint.y()) / squareSize;
			AddressOnBlocksDescription address(AddressOnBlocksDescription::orientation::VERTICAL, squareX, squareY);
			moveAndShowTextBox(address);
		}
	} else {
		hideTextBox();
	}
}

bool ColumnsDescriptionView::isPointOnDefinedDescription(QPoint screenPoint)
{
	size_t squareX = static_cast<size_t>(screenPoint.x()) / squareSize;
	size_t squareY = static_cast<size_t>(screenPoint.y()) / squareSize;
	return (field->isDefinedColumnDescriptionAt(squareX, squareY));
}

void ColumnsDescriptionView::redrawAll()
{
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
	int screenX = static_cast<int>(squareSize * address.getLine());
	int screenY = static_cast<int>(squareSize * address.getCount());
	
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
	size_t squareX = qTextEdit->pos().x() / squareSize;
	size_t squareY = qTextEdit->pos().y() / squareSize;
	AddressOnBlocksDescription address = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, squareX, squareY);
	QString textFromBox = qTextEdit->toPlainText();
	size_t blockSize = textFromBox.toInt();
	BlockDescription blockDecription = BlockDescription(address, blockSize);
	field->updateBlockDescription(blockDecription);
}

void ColumnsDescriptionView::moveAndShowTextBox(AddressOnBlocksDescription address)
{
	int x = squareSize * address.getLine();
	int y = squareSize * address.getCount();
	qTextEdit->move(x, y);
	qTextEdit->show();
	qTextEdit->setFocus();
	qTextEdit->selectAll();
}


void ColumnsDescriptionView::resize(const QSize &newSize)
{
	setMinimumSize(newSize);		// for scroll area, minimum size - you cannot shrink window size lower than this	
	
	// init image:
	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));
	image = newImage;
}
