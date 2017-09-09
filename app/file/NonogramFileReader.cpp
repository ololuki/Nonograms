/**********************************************************************
 * Copyright (C) 2017 Ololuki
 * https://ololuki.pl
 * 
 * This file is part of Nonograms
 * https://github.com/ololuki/nonograms
 * 
 * Nonograms is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Nonograms is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Nonograms.  If not, see <http://www.gnu.org/licenses/>.
 *********************************************************************/
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
	switch (orientation)
	{
	case AddressOnBlocksDescription::VERTICAL:
		field->columnsDescription()->deleteDescription(BlockDescription(AddressOnBlocksDescription(orientation, lineNumber, lineLength), 0));
		break;
	case AddressOnBlocksDescription::HORIZONTAL:
		field->rowsDescription()->deleteDescription(BlockDescription(AddressOnBlocksDescription(orientation, lineNumber, lineLength), 0));
		break;
	}

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
	switch (address.getOrientation())
	{
	case AddressOnBlocksDescription::VERTICAL:
		field->columnsDescription()->insertDescriptionBefore(BlockDescription(address, blockSize));
		break;
	case AddressOnBlocksDescription::HORIZONTAL:
		field->rowsDescription()->insertDescriptionBefore(BlockDescription(address, blockSize));
		break;
	}
}
