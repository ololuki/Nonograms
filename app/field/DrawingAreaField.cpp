#include "DrawingAreaField.h"
#include <QDebug>


DrawingAreaField::DrawingAreaField(int width, int height) : array(width, height)
{
	qDebug() << "DrawingAreaField width height c-tor";
}

DrawingAreaField::~DrawingAreaField()
{
	qDebug() << "DrawingAreaField d-tor";
}

Pixel DrawingAreaField::getPixel(AddressOnDrawingArea address) const
{
	int x = address.getX();
	int y = address.getY();
	return array.getPixelAt(x, y);
}

void DrawingAreaField::setPixel(Pixel pixel)
{
	int x = pixel.getAddress().getX();
	int y = pixel.getAddress().getY();
	array(x, y) = pixel;
	emit pixelChanged(pixel.getAddress());
}
