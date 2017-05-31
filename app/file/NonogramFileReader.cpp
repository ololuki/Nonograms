#include "NonogramFileReader.h"

#include <QJsonDocument>
#include <QFile>
#include "field/WholeFieldImpl.h"


NonogramFileReader::NonogramFileReader()
{
	
}

NonogramFileReader::~NonogramFileReader()
{
	
}

std::shared_ptr<WholeField> NonogramFileReader::getField()
{
	return field;
}

bool NonogramFileReader::read(const std::string &fileDir)
{
	QFile fileToRead(QString::fromUtf8(fileDir.c_str()));
	if (!fileToRead.open(QIODevice::ReadOnly)) {
		return false;
	}
	
	QByteArray fileData = fileToRead.readAll();
	QJsonDocument jsonDoc(QJsonDocument::fromJson(fileData));
	
	QJsonObject jsonObj = jsonDoc.object();
	QJsonObject jsonSize = jsonObj["size"].toObject();
	size_t width;
	size_t height;
	readSize(width, height, jsonSize);
	field.reset(new WholeFieldImpl(width, height));
	QJsonArray drawingArea = jsonObj["drawingArea"].toArray();
	readDrawingArea(drawingArea);
	
	return true;
}

void NonogramFileReader::readSize(size_t &width, size_t &height, QJsonObject jsonSize)
{
	width = static_cast<size_t>(jsonSize["width"].toInt());
	height = static_cast<size_t>(jsonSize["height"].toInt());
}

void NonogramFileReader::readDrawingArea(QJsonArray drawingArea)
{
	for(int i = 0; i < drawingArea.size(); i++)
	{
		QJsonObject jsonPixel = drawingArea[i].toObject();
		Pixel pixel = readPixel(jsonPixel);
		field->setPixel(pixel);
	}
}

Pixel NonogramFileReader::readPixel(QJsonObject jsonPixel)
{
	size_t addressX = static_cast<size_t>(jsonPixel["addressX"].toInt());
	size_t addressY = static_cast<size_t>(jsonPixel["addressY"].toInt());
	AddressOnDrawingArea address(addressX, addressY);
	Pixel pixel = Pixel(address);
	if (jsonPixel["sign"].toString() == "empty") pixel.makeEmpty();
	else if (jsonPixel["sign"].toString() == "dot") pixel.makeDot();
	else if (jsonPixel["sign"].toString() == "fillBlack") pixel.makeFilledBlack();
	return pixel;
}
