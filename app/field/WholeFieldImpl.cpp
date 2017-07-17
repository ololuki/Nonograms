#include "WholeFieldImpl.h"
#include "AllLinesDescription.h"

#include <QDebug>


WholeFieldImpl::WholeFieldImpl(size_t width, size_t height) : RootField(width, height)
{
	array = ArrayOfPixels(width, height);
	columnsDescription = AllLinesDescription(AddressOnBlocksDescription::VERTICAL, width);
	rowsDescription = AllLinesDescription(AddressOnBlocksDescription::HORIZONTAL, height);
	qDebug() << "construct whole field";
}

WholeFieldImpl::~WholeFieldImpl()
{
	qDebug() << "destruct whole field";
}

void WholeFieldImpl::clearDrawingArea()
{
	for (size_t i = 0; i < getWidth(); i++)
	{
		for (size_t j = 0; j < getHeight(); j++)
		{
			setPixel(Pixel(AddressOnDrawingArea(i, j)));
		}
	}
}

void WholeFieldImpl::clearBlocksDescription()
{
	// TODO
}
