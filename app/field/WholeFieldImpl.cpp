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
	emit pixelChanged(pixel.getAddress());
}

BlockDescription WholeFieldImpl::getBlockDescription(AddressOnBlocksDescription address)
{
	if (address.isColumn())
	{
		return columnsDescription(address.getLine(), address.getCount());
	} else {
		return rowsDescription(address.getLine(), address.getCount());
	}
}

void WholeFieldImpl::updateBlockDescription(BlockDescription blockDescription)
{
	if (blockDescription.getAddress().isColumn())
	{
		columnsDescription.updateDescription(blockDescription);
	} else {
		rowsDescription.updateDescription(blockDescription);
	}
	emit dataChanged();
}

void WholeFieldImpl::insertDescriptionBefore(BlockDescription blockDescription)
{
	if (blockDescription.getAddress().isColumn())
	{
		columnsDescription.insertDescriptionBefore(blockDescription);
	} else {
		rowsDescription.insertDescriptionBefore(blockDescription);
	}
	emit dataChanged();
}

void WholeFieldImpl::addDescriptionAtEnd(BlockDescription blockDescription)
{
	if (blockDescription.getAddress().isColumn())
	{
		columnsDescription.addDescriptionAtEnd(blockDescription);
	} else {
		rowsDescription.addDescriptionAtEnd(blockDescription);
	}
	emit dataChanged();
}

void WholeFieldImpl::deleteDescription(BlockDescription blockDescription)
{
	if (blockDescription.getAddress().isColumn())
	{
		columnsDescription.deleteDescription(blockDescription);
	} else {
		rowsDescription.deleteDescription(blockDescription);
	}
	emit dataChanged();
}

size_t WholeFieldImpl::numberOfBlocksInColumn(size_t columnNumber)
{
	return columnsDescription.numberOfBlocksInLine(columnNumber);
}

size_t WholeFieldImpl::numberOfBlocksInRow(size_t rowNumber)
{
	return rowsDescription.numberOfBlocksInLine(rowNumber);
}

size_t WholeFieldImpl::columnsDescriptionHeight()
{
	size_t height = 0;
	for (size_t i = 0; i < getWidth(); i++)
	{
		height = std::max(height, columnsDescription.numberOfBlocksInLine(i));
	}
	return height;
}

size_t WholeFieldImpl::rowsDescriptionWidth()
{
	size_t width = 0;
	for (size_t i = 0; i < getHeight(); i++)
	{
		width = std::max(width, rowsDescription.numberOfBlocksInLine(i));
	}
	return width;
}

bool WholeFieldImpl::isDefinedColumnDescriptionAt(AddressOnBlocksDescription address)
{
	if (address.isColumn())
	{
		return columnsDescription.isDefinedDescriptionAt(address.getLine(), address.getCount());
	} else {
		return rowsDescription.isDefinedDescriptionAt(address.getLine(), address.getCount());
	}
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
