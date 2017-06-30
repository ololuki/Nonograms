#include "DrawingAreaView.h"
#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QSize>


DrawingAreaView::DrawingAreaView(QWidget *parent)
    : QWidget(parent)
{
	setAttribute(Qt::WA_StaticContents); 
	myPenWidth = 1;
	myPenColor = Qt::black;
	
	QSize size(211, 211);
	resizeDrawingArea(size);
	
	lastPoint = QPoint(0, 0);
}

void DrawingAreaView::setField(std::shared_ptr<DrawingAreaField> field)
{
	this->field = field;
	connect(static_cast<DrawingAreaField*>(this->field.get()), &DrawingAreaField::dataChanged, this, &DrawingAreaView::onDataChanged);
	connect(static_cast<DrawingAreaField*>(this->field.get()), &DrawingAreaField::pixelChanged, this, &DrawingAreaView::onPixelChanged);
	
	size_t sizeX = field->getWidth() * squareSize + 1;
	size_t sizeY = field->getHeight() * squareSize + 1;
	QSize size(sizeX, sizeY);
	resizeDrawingArea(size);
	
	drawGrid();
}

void DrawingAreaView::onDataChanged()
{
	for (size_t y = 0; y < field->getHeight(); y++)
	{
		for (size_t x = 0; x < field->getWidth(); x++)
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
	
	size_t pixelX = currentPoint.x() / squareSize;
	size_t pixelY = currentPoint.y() / squareSize;
	
	if (pixelX >= field->getWidth()) return;
	if (pixelY >= field->getHeight()) return;
	
	Pixel pixel(AddressOnDrawingArea(pixelX, pixelY));
	switch(event->button())
	{
	case Qt::LeftButton:
		pixel.makeFilledBlack();
		break;
	case Qt::RightButton:
		pixel.makeDot();
		break;
	case Qt::MiddleButton:
		pixel.makeEmpty();
		break;
	default:
		break;
	}
	field->setPixel(pixel);
}

void DrawingAreaView::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QRect dirtyRect = event->rect();
	painter.drawImage(dirtyRect, image, dirtyRect);
}

void DrawingAreaView::drawGrid()
{
	QPainter p(&image);
	p.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	for (int y = 0; y < field->getHeight(); y++)
	{
		for (int x = 0; x < field->getWidth(); x++)
		{
			int currentX = x * squareSize;
			int currentY = y * squareSize;
			QRect rectangle = QRect(currentX, currentY, squareSize, squareSize);
			p.drawRect(rectangle);
		}
	}
}

void DrawingAreaView::drawOnePixel(Pixel pixel)
{
	QPainter painter(&image);
	painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	
	int x = pixel.getAddress().getX();
	int y = pixel.getAddress().getY();
	
	int currentX = x * squareSize;
	int currentY = y * squareSize;
	QRect rectangle = QRect(currentX, currentY, squareSize, squareSize);
	
	if (pixel.isFilledBlack()) {
		painter.fillRect(rectangle, Qt::black);
	} else if (pixel.isDot()) {
		painter.fillRect(rectangle, Qt::white);
		QPoint centerP(currentX + squareSize / 2, currentY + squareSize / 2);
		painter.drawEllipse(centerP, squareSize / 10, squareSize / 10);
	}else if (pixel.isEmpty()) {
		painter.fillRect(rectangle, Qt::white);
	}
	painter.drawRect(rectangle);
}

void DrawingAreaView::resizeDrawingArea(const QSize &newSize)
{
	setMinimumSize(newSize);		// for scroll area, minimum size - you cannot shrink window size lower than this	
	
	// init image:
	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));
	image = newImage;
}
