#ifndef FILEREADER_H
#define FILEREADER_H

#include <memory>
#include "field/WholeField.h"


///
/// \brief Interface
///
class FileReader
{
public:
	virtual ~FileReader() {}
	
	virtual WholeField getField() = 0;
	virtual bool read(const std::string &fileDir) = 0;
};

#endif // FILEREADER_H
