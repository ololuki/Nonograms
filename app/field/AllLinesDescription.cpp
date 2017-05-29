#include "AllLinesDescription.h"

AllLinesDescription::AllLinesDescription(AddressOnBlocksDescription::orientation orientation, size_t numberOfLines)
{
	const size_t defaultBlockSize = 0;
	for(size_t i = 0; i < numberOfLines; i++)
	{
		AddressOnBlocksDescription address = AddressOnBlocksDescription(orientation, i, 0);
		std::vector<BlockDescription> line;
		line.push_back(BlockDescription(address, defaultBlockSize));
		lines.push_back(line);
	}
}

size_t AllLinesDescription::numberOfBlocksInLine(size_t lineNumber)
{
	return lines[lineNumber].size();
}

bool AllLinesDescription::isDefinedDescriptionAt(size_t line, size_t count)
{
	if (line >= lines.size()) return false;
	if (count >= lines[line].size()) return false;
	return true;
}

void AllLinesDescription::updateDescription(BlockDescription blockDescription)
{
	AddressOnBlocksDescription address = blockDescription.getAddress();
	if (address.getCount() >= lines[address.getLine()].size()) return;
	lines[address.getLine()][address.getCount()] = blockDescription;
}

void AllLinesDescription::insertDescriptionBefore(BlockDescription blockDescription)
{
	size_t line = blockDescription.getAddress().getLine();
	size_t count = blockDescription.getAddress().getCount();
	size_t length = lines[line].size();
	AddressOnBlocksDescription::orientation orientation = blockDescription.getAddress().getOrientation();
	if (count >= length) return;
	
	AddressOnBlocksDescription addressOfNewLast = AddressOnBlocksDescription(orientation, line, length);
	
	BlockDescription newLastBlock = lines[line][length - 1];
	newLastBlock.updateAddress(addressOfNewLast);
	lines[line].push_back(newLastBlock);
	
	for (size_t i = length; i-- > count + 1;)
	{
		lines[line][i].setBlockSize( lines[line][i-1].getBlockSize());
	}
	lines[line][count] = blockDescription;
}

void AllLinesDescription::addDescriptionAtEnd(BlockDescription blockDescription)
{
	size_t line = blockDescription.getAddress().getLine();
	size_t count = blockDescription.getAddress().getCount();
	if (lines[line].size() == count)
	{
		lines[line].push_back(blockDescription);
	}
}

void AllLinesDescription::deleteDescription(BlockDescription blockDescription)
{
	size_t line = blockDescription.getAddress().getLine();
	size_t count = blockDescription.getAddress().getCount();
	if (lines[line].size() <= 1) return;
	size_t newLength = lines[line].size() - 1;
	for(size_t i = count; i < newLength; i++)
	{
		lines[line][i].setBlockSize( lines[line][i+1].getBlockSize());
	}
	lines[line].pop_back();
}
