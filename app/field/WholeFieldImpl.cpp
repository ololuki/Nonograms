#include "WholeFieldImpl.h"
#include "AllLinesDescription.h"

#include <QDebug>


WholeFieldImpl::WholeFieldImpl(size_t width, size_t height)
	: RootField(width, height),
	  WholeField(width, height)
{
	columnsDescription = AllLinesDescription(AddressOnBlocksDescription::VERTICAL, width);
	rowsDescription = AllLinesDescription(AddressOnBlocksDescription::HORIZONTAL, height);
	qDebug() << "WholeFieldImpl width height c-tor";
}

WholeFieldImpl::WholeFieldImpl(const WholeField &field)
	: RootField(field.getWidth(), field.getHeight()),
	  WholeField(field)
{
	columnsDescription = field.columnsDescription;
	rowsDescription = field.rowsDescription;
	qDebug() << "WholeFieldImpl copy c-tor";
}

WholeFieldImpl::~WholeFieldImpl()
{
	qDebug() << "WholeFieldImpl d-tor";
}

void WholeFieldImpl::clearDrawingArea()
{
	for (size_t i = 0; i < getWidth(); i++)
	{
		for (size_t j = 0; j < getHeight(); j++)
		{
			drawingArea()->setPixel(Pixel(AddressOnDrawingArea(i, j)));
		}
	}
}

void WholeFieldImpl::clearBlocksDescription()
{
	// TODO
}
