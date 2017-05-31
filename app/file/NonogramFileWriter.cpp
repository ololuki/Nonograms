#include "NonogramFileWriter.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>


NonogramFileWriter::NonogramFileWriter()
{
	
}

NonogramFileWriter::~NonogramFileWriter()
{
	
}

void NonogramFileWriter::setField(std::shared_ptr<WholeField> field)
{
	this->field = field;
}

bool NonogramFileWriter::write(const std::string &fileDir)
{
	QFile fileToSave(QString::fromUtf8(fileDir.c_str()));
	if (!fileToSave.open(QIODevice::WriteOnly)) {
		return false;
	}
	
	QJsonObject jsonObj;
	jsonObj["size"] = writeSize(field);
	jsonObj["drawingArea"] = writeDrawingArea(field);
	
	QJsonDocument jsonDoc(jsonObj);
	fileToSave.write(jsonDoc.toJson());
	return true;
}

QJsonObject NonogramFileWriter::writeSize(std::shared_ptr<WholeField> field)
{
	QJsonObject size;
	size["width"] = static_cast<int>(field->getWidth());
	size["height"] = static_cast<int>(field->getHeight());
	return size;
}

QJsonArray NonogramFileWriter::writeDrawingArea(std::shared_ptr<WholeField> field)
{
	QJsonArray drawingArea;
	for (size_t y = 0; y < field->getHeight(); y++)
	{
		for (size_t x = 0; x < field->getWidth(); x++)
		{
			AddressOnDrawingArea address(x, y);
			Pixel pixel = field->getPixel(address);
			drawingArea.append(writePixel(pixel));
		}
	}
	return drawingArea;
}

QJsonObject NonogramFileWriter::writePixel(Pixel pixel)
{
	QJsonObject jsonPixel;
	jsonPixel["sign"] = pixel.isDot() ? "dot" : (pixel.isFilledBlack() ? "fillBlack" : "empty");
	jsonPixel["addressX"] = static_cast<int>(pixel.getAddress().getX());
	jsonPixel["addressY"] = static_cast<int>(pixel.getAddress().getY());
	return jsonPixel;
}
