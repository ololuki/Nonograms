#include "AllLinesDescription.h"

AllLinesDescription::AllLinesDescription(AddressOnBlocksDescription::orientation orientation, size_t numberOfLines)
{
	switch(orientation)
	{
	case AddressOnBlocksDescription::VERTICAL:
		for(size_t i = 0; i < numberOfLines; i++)
		{
			AddressOnBlocksDescription address = AddressOnBlocksDescription(orientation, i, 0);
			std::vector<BlockDescription> line;
			line.push_back(BlockDescription(address, 0));
			lines.push_back(line);
		}
		break;
	case AddressOnBlocksDescription::HORIZONTAL:
		// TODO
		break;
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
	lines[address.getLine()][address.getCount()] = blockDescription;
}
