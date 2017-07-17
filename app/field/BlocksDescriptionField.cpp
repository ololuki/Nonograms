#include "BlocksDescriptionField.h"


BlockDescription BlocksDescriptionField::getBlockDescription(AddressOnBlocksDescription address)
{
	if (address.isColumn())
	{
		return columnsDescription(address.getLine(), address.getCount());
	} else {
		return rowsDescription(address.getLine(), address.getCount());
	}
}

void BlocksDescriptionField::updateBlockDescription(BlockDescription blockDescription)
{
	if (blockDescription.getAddress().isColumn())
	{
		columnsDescription.updateDescription(blockDescription);
	} else {
		rowsDescription.updateDescription(blockDescription);
	}
	emit dataChanged();
}

void BlocksDescriptionField::insertDescriptionBefore(BlockDescription blockDescription)
{
	if (blockDescription.getAddress().isColumn())
	{
		columnsDescription.insertDescriptionBefore(blockDescription);
	} else {
		rowsDescription.insertDescriptionBefore(blockDescription);
	}
	emit dataChanged();
}

void BlocksDescriptionField::addDescriptionAtEnd(BlockDescription blockDescription)
{
	if (blockDescription.getAddress().isColumn())
	{
		columnsDescription.addDescriptionAtEnd(blockDescription);
	} else {
		rowsDescription.addDescriptionAtEnd(blockDescription);
	}
	emit dataChanged();
}

void BlocksDescriptionField::deleteDescription(BlockDescription blockDescription)
{
	if (blockDescription.getAddress().isColumn())
	{
		columnsDescription.deleteDescription(blockDescription);
	} else {
		rowsDescription.deleteDescription(blockDescription);
	}
	emit dataChanged();
}

size_t BlocksDescriptionField::numberOfBlocksInColumn(size_t columnNumber)
{
	return columnsDescription.numberOfBlocksInLine(columnNumber);
}

size_t BlocksDescriptionField::numberOfBlocksInRow(size_t rowNumber)
{
	return rowsDescription.numberOfBlocksInLine(rowNumber);
}

size_t BlocksDescriptionField::columnsDescriptionHeight()
{
	size_t height = 0;
	for (size_t i = 0; i < getWidth(); i++)
	{
		height = std::max(height, columnsDescription.numberOfBlocksInLine(i));
	}
	return height;
}

size_t BlocksDescriptionField::rowsDescriptionWidth()
{
	size_t width = 0;
	for (size_t i = 0; i < getHeight(); i++)
	{
		width = std::max(width, rowsDescription.numberOfBlocksInLine(i));
	}
	return width;
}

bool BlocksDescriptionField::isDefinedColumnDescriptionAt(AddressOnBlocksDescription address)
{
	if (address.isColumn())
	{
		return columnsDescription.isDefinedDescriptionAt(address.getLine(), address.getCount());
	} else {
		return rowsDescription.isDefinedDescriptionAt(address.getLine(), address.getCount());
	}
}
