#include "DrawingAreaView.h"
#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QtWidgets>
#include "iostream"

DrawingAreaView::DrawingAreaView(QWidget *parent)
    : QWidget(parent)
{
	setAttribute(Qt::WA_StaticContents); 
	myPenWidth = 1;
	myPenColor = Qt::black;
	
	QSize size(211, 211);
	resizeDrawingArea(size);
	//setMinimumSize(211, 211);		// for scroll area
	
	lastPoint = QPoint(0, 0);
}

void DrawingAreaView::setField(DrawingAreaField *field)
{
	this->field = field;
	connect(field, &DrawingAreaField::dataChanged, this, &DrawingAreaView::onDataChanged);
	
	int sizeX = field->getWidth() * squareSize + 1;
	int sizeY = field->getHeight() * squareSize + 1;
	QSize size(sizeX, sizeY);
	resizeDrawingArea(size);
	
	drawGrid();
}

void DrawingAreaView::onDataChanged()
{
	std::cout << "DrawingArea::onDataChanged" << std::endl;
	for (int y = 0; y < field->getHeight(); y++)
	{
		for (int x = 0; x < field->getWidth(); x++)
		{
			AddressOnDrawingArea address(x, y);
			//drawOnePixel(field->getPixel(address));
		}
	}
	drawGrid();
	update();
}

void DrawingAreaView::mousePressEvent(QMouseEvent *event)
{
	QPoint currentPoint = event->pos();
	
	int pixelX = currentPoint.x() / squareSize;
	int pixelY = currentPoint.y() / squareSize;
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
	}
	drawOnePixel(pixel);
	field->setPixel(pixel);
	update();
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
