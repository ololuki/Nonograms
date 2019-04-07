#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <memory>
#include "field/WholeFieldModel.h"


///
/// \brief Interface
///
class FileWriter
{
public:
	virtual ~FileWriter() {}
	
	virtual void setField(const WholeField& field) = 0;
	virtual bool write(const std::string &fileDir) = 0;
};

#endif // FILEWRITER_H
