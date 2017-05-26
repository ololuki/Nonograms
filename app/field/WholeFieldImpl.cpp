#include "WholeFieldImpl.h"
#include "AllLinesDescription.h"


WholeFieldImpl::WholeFieldImpl(size_t width, size_t height) : RootField(width, height)
{
	array = ArrayOfPixels(width, height);
	columnsDescription = AllLinesDescription(AddressOnBlocksDescription::orientation::VERTICAL, width);
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

BlockDescription WholeFieldImpl::getBlockDescription(AddressOnBlocksDescription address)
{
	BlockDescription blockDescription = columnsDescription(address.getLine(), address.getCount());
	return blockDescription;
}

void WholeFieldImpl::updateBlockDescription(BlockDescription blockDescription)
{
	if (blockDescription.getAddress().isColumn())
	{
		columnsDescription.updateDescription(blockDescription);
	}
	emit dataChanged();
}

size_t WholeFieldImpl::numberOfBlocksInColumn(size_t columnNumber)
{
	return columnsDescription.numberOfBlocksInLine(columnNumber);
}

bool WholeFieldImpl::isDefinedColumnDescriptionAt(size_t line, size_t count)
{
	return columnsDescription.isDefinedDescriptionAt(line, count);
}
