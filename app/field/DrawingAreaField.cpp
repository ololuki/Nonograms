#include "DrawingAreaField.h"


Pixel DrawingAreaField::getPixel(AddressOnDrawingArea address) const
{
	size_t x = address.getX();
	size_t y = address.getY();
	return array.getPixelAt(x, y);
}

void DrawingAreaField::setPixel(Pixel pixel)
{
	size_t x = pixel.getAddress().getX();
	size_t y = pixel.getAddress().getY();
	array(x, y) = pixel;
	emit pixelChanged(pixel.getAddress());
}
