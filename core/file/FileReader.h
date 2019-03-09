#ifndef FILEREADER_H
#define FILEREADER_H

#include <memory>
#include "field/WholeFieldModel.h"


///
/// \brief Interface
///
class FileReader
{
public:
	virtual ~FileReader() {}
	
	virtual std::shared_ptr<WholeFieldModel> getField() = 0;
	virtual bool read(const std::string &fileDir) = 0;
};

#endif // FILEREADER_H
