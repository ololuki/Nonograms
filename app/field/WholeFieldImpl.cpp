#include "WholeFieldImpl.h"


WholeFieldImpl::WholeFieldImpl(size_t width, size_t height) : RootField(width, height)
{
	array = ArrayOfPixels(width, height);
}

Pixel WholeFieldImpl::getPixel(AddressOnDrawingArea address)
{
	size_t x = address.getX();
	size_t y = address.getY();
	return array(x, y);
}

void WholeFieldImpl::setPixel(Pixel pixel)
{
	size_t x = pixel.getAddress().getX();
	size_t y = pixel.getAddress().getY();
	array(x, y) = pixel;
	emit dataChanged();
}
