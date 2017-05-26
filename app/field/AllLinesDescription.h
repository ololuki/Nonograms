#ifndef ALLLINESDESCRIPTION_H
#define ALLLINESDESCRIPTION_H

#include <vector>
#include "field/BlockDescription.h"
#include "field/LineDescription.h"


///
/// \brief AllLinesDescription contains all descriptions for columns or rows.
/// It stores BlockDescription in vector of vectors.
///
class AllLinesDescription
{
public:
	AllLinesDescription() {}
	AllLinesDescription(AddressOnBlocksDescription::orientation orientation, size_t numberOfLines);
	size_t numberOfBlocksInLine(size_t lineNumber);
	bool isDefinedDescriptionAt(size_t line, size_t count);	// true if BlockDescription exists on given position
	void updateDescription(BlockDescription blockDescription);
	//void insertDescriptionBefore(size_t line, size_t count);
	//void addDescriptionAtEnd(size_t line);
	//void deleteDescriptionAt(size_t line, size_t count);
	BlockDescription& operator()(size_t line, size_t count)
	{
		return lines[line][count];
	}
private:
	std::vector<std::vector<BlockDescription>> lines;
};

#endif // ALLLINESDESCRIPTION_H
