#ifndef NONOGRAMFILEWRITER_H
#define NONOGRAMFILEWRITER_H

#include "FileWriter.h"
#include <QJsonObject>
#include <QJsonArray>

#include "field/Pixel.h"


class NonogramFileWriter : public FileWriter
{
public:
	NonogramFileWriter();
	~NonogramFileWriter();
	
	void setField(std::shared_ptr<WholeField> field) override;
	bool write(const std::string &fileDir) override;
	
private:
	std::shared_ptr<WholeField> field;
	
	QJsonObject writeSize(std::shared_ptr<WholeField> field);
	QJsonArray writeDrawingArea(std::shared_ptr<WholeField> field);
	QJsonObject writePixel(Pixel pixel);
};

#endif // NONOGRAMFILEWRITER_H
