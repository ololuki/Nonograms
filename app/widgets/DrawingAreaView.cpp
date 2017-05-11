#include "DrawingAreaView.h"
#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QtWidgets>


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
	drawGrid();
}

void DrawingAreaView::mousePressEvent(QMouseEvent *event)
{
	QPoint currentPoint = event->pos();
		
	QPainter painter(&image);
	painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		
	// square - mój prostokąt:
	const int squareSize = 30;
	int currentX = currentPoint.x() / squareSize * squareSize;
	int currentY = currentPoint.y() / squareSize * squareSize;
	QRect rectangle = QRect(currentX, currentY, squareSize, squareSize);
	
	if (event->button() == Qt::LeftButton) {
		painter.fillRect(rectangle, Qt::black);
	}
	if (event->button() == Qt::RightButton) {
		painter.fillRect(rectangle, Qt::yellow);
	}
	if (event->button() == Qt::MiddleButton) {
		painter.fillRect(rectangle, Qt::white);
	}
	painter.drawRect(rectangle);
	
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
	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			int currentX = x * squareSize;
			int currentY = y * squareSize;
			QRect rectangle = QRect(currentX, currentY, squareSize, squareSize);
			p.drawRect(rectangle);
		}
	}
}

void DrawingAreaView::resizeDrawingArea(const QSize &newSize)
{
	setMinimumSize(newSize);		// for scroll area, minimum size - you cannot shrink window size lower than this	
	
	// init image:
	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));
	image = newImage;
}
