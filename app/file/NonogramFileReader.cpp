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
	parseSize(width, height, jsonSize);
	field.reset(new WholeFieldImpl(width, height));
	QJsonArray drawingArea = jsonObj["drawingArea"].toArray();
	parseDrawingArea(drawingArea);
	
	QJsonArray columnsDescription = jsonObj["columnsDescription"].toArray();
	parseColumnsDescription(columnsDescription);
	
	QJsonArray rowsDescription = jsonObj["rowsDescription"].toArray();
	parseRowsDescription(rowsDescription);
	
	return true;
}

void NonogramFileReader::parseSize(size_t &width, size_t &height, QJsonObject jsonSize)
{
	width = static_cast<size_t>(jsonSize["width"].toInt());
	height = static_cast<size_t>(jsonSize["height"].toInt());
}

void NonogramFileReader::parseDrawingArea(QJsonArray drawingArea)
{
	for(int i = 0; i < drawingArea.size(); i++)
	{
		QJsonObject jsonPixel = drawingArea[i].toObject();
		Pixel pixel = parsePixel(jsonPixel);
		field->drawingArea()->setPixel(pixel);
	}
}

Pixel NonogramFileReader::parsePixel(QJsonObject jsonPixel)
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

void NonogramFileReader::parseColumnsDescription(QJsonArray columnsDescription)
{
	for (size_t i = 0; i < columnsDescription.size(); i++)
	{
		QJsonObject jsonLineDescription = columnsDescription[i].toObject();
		parseLineDescription(jsonLineDescription, i, AddressOnBlocksDescription::VERTICAL);
	}
}

void NonogramFileReader::parseRowsDescription(QJsonArray rowsDescription)
{
	for (size_t i = 0; i < rowsDescription.size(); i++)
	{
		QJsonObject jsonLineDescription = rowsDescription[i].toObject();
		parseLineDescription(jsonLineDescription, i, AddressOnBlocksDescription::HORIZONTAL);
	}
}

void NonogramFileReader::parseLineDescription(QJsonObject jsonLineDescription, size_t lineNumber, AddressOnBlocksDescription::orientation orientation)
{
	size_t lineLength = jsonLineDescription["lineLength"].toInt();
	QJsonArray blocksDescriptionArray = jsonLineDescription["lineDescription"].toArray();
	parseArrayOfBlockDescription(blocksDescriptionArray, lineNumber, lineLength, orientation);
	field->deleteDescription(BlockDescription(AddressOnBlocksDescription(orientation, lineNumber, lineLength), 0));
}

void NonogramFileReader::parseArrayOfBlockDescription(QJsonArray jsonArray, size_t lineNumber, size_t lineLength, AddressOnBlocksDescription::orientation orientation)
{
	for (size_t i = 0; i < lineLength; i++)
	{
		AddressOnBlocksDescription address = AddressOnBlocksDescription(orientation, lineNumber, i);
		QJsonObject jsonBlockDescription = jsonArray[i].toObject();
		parseBlockDescription(jsonBlockDescription, address);
	}
}

void NonogramFileReader::parseBlockDescription(QJsonObject jsonBlockDescription, AddressOnBlocksDescription address)
{
	size_t blockSize = jsonBlockDescription["blockSize"].toInt();
	field->insertDescriptionBefore(BlockDescription(address, blockSize));
}
