#ifndef NONOGRAMFILEWRITER_H
#define NONOGRAMFILEWRITER_H

#include "FileWriter.h"
#include <QJsonObject>
#include <QJsonArray>

#include "field/Pixel.h"
#include "field/LineDescription.h"
#include "field/BlockDescription.h"


///
/// Serialize whole field to JSON and writes it to file
///
class NonogramFileWriter : public FileWriter
{
public:
	NonogramFileWriter();
	~NonogramFileWriter();
	
	void setField(std::shared_ptr<WholeField> field) override;
	bool write(const std::string &fileDir) override;
	
private:
	std::shared_ptr<WholeField> field;
	
	QJsonObject serializeSize();
	QJsonArray serializeDrawingArea();
	QJsonObject serializePixel(Pixel pixel);
	
	QJsonArray serializeColumnsDescription();
	QJsonArray serializeRowsDescription();
	QJsonObject serializeLineDescription(size_t lineNumber, AddressOnBlocksDescription::orientation orientation);
	QJsonArray serializeArrayOfBlockDescription(size_t lineNumber, size_t lineLength, AddressOnBlocksDescription::orientation orientation);
	QJsonObject serializeBlockDescription(AddressOnBlocksDescription address);
};

#endif // NONOGRAMFILEWRITER_H
