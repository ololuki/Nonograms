#include "WholeFieldImpl.h"


Pixel WholeFieldImpl::getPixel(AddressOnDrawingArea address)
{
	unsigned int x = address.getX();
	unsigned int y = address.getY();
	return array[x][y];
}

void WholeFieldImpl::setPixel(Pixel pixel)
{
	unsigned int x = pixel.getAddress().getX();
	unsigned int y = pixel.getAddress().getY();
	array[x][y] = pixel;
	emit dataChanged();
}
