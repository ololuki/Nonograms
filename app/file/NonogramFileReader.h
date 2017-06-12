#ifndef NONOGRAMFILEREADER_H
#define NONOGRAMFILEREADER_H

#include "file/FileReader.h"
#include <QJsonObject>
#include <QJsonArray>

#include "field/Pixel.h"


///
/// Reading from file and parsing JSON to whole field
///
class NonogramFileReader : public FileReader
{
public:
	NonogramFileReader();
	~NonogramFileReader();
	
	std::shared_ptr<WholeField> getField() override;
	bool read(const std::string &fileDir) override;
	
private:
	std::shared_ptr<WholeField> field;
	
	void parseSize(size_t &width, size_t &height, QJsonObject jsonSize);
	void parseDrawingArea(QJsonArray drawingArea);
	Pixel parsePixel(QJsonObject jsonPixel);
	
	void parseColumnsDescription(QJsonArray columnsDescription);
	void parseRowsDescription(QJsonArray rowsDescription);
	void parseLineDescription(QJsonObject jsonLineDescription, size_t lineNumber, AddressOnBlocksDescription::orientation orientation);
	void parseArrayOfBlockDescription(QJsonArray jsonArray, size_t lineNumber, size_t lineLength, AddressOnBlocksDescription::orientation orientation);
	void parseBlockDescription(QJsonObject jsonBlockDescription, AddressOnBlocksDescription address);
};

#endif // NONOGRAMFILEREADER_H
