#ifndef LINEDESCRIPTION_H
#define LINEDESCRIPTION_H

#include <vector>
#include "field/BlockDescription.h"

///
/// \brief LineDescription contains BlockDescriptions for one line of picture
///
class LineDescription : std::vector<BlockDescription>
{
public:
	LineDescription() {}
	LineDescription(std::vector<BlockDescription> vectorToCopy) : std::vector<BlockDescription>(vectorToCopy) {}
	size_t size() {return std::vector<BlockDescription>::size();}
	
	//BlockDescription& getPixelAt(const unsigned int count) {return this->at(count);}
	BlockDescription& operator[](const unsigned int count) {return std::vector<BlockDescription>::operator[](count);}
};

#endif // LINEDESCRIPTION_H
