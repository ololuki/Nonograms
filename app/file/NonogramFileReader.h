#ifndef NONOGRAMFILEREADER_H
#define NONOGRAMFILEREADER_H

#include "file/FileReader.h"
#include <QJsonObject>
#include <QJsonArray>

#include "field/Pixel.h"


class NonogramFileReader : public FileReader
{
public:
	NonogramFileReader();
	~NonogramFileReader();
	
	std::shared_ptr<WholeField> getField() override;
	bool read(const std::string &fileDir) override;
	
private:
	std::shared_ptr<WholeField> field;
	
	void readSize(size_t &width, size_t &height, QJsonObject jsonSize);
	void readDrawingArea(QJsonArray drawingArea);
	Pixel readPixel(QJsonObject jsonPixel);
};

#endif // NONOGRAMFILEREADER_H
