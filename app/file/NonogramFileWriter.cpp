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
	jsonObj["size"] = serializeSize();
	jsonObj["drawingArea"] = serializeDrawingArea();
	jsonObj["columnsDescription"] = serializeColumnsDescription();
	jsonObj["rowsDescription"] = serializeRowsDescription();
	
	QJsonDocument jsonDoc(jsonObj);
	fileToSave.write(jsonDoc.toJson());
	return true;
}

QJsonObject NonogramFileWriter::serializeSize()
{
	QJsonObject size;
	size["width"] = static_cast<int>(field->getWidth());
	size["height"] = static_cast<int>(field->getHeight());
	return size;
}

QJsonArray NonogramFileWriter::serializeDrawingArea()
{
	QJsonArray drawingArea;
	for (size_t y = 0; y < field->getHeight(); y++)
	{
		for (size_t x = 0; x < field->getWidth(); x++)
		{
			AddressOnDrawingArea address(x, y);
			Pixel pixel = field->drawingArea()->getPixel(address);
			drawingArea.append(serializePixel(pixel));
		}
	}
	return drawingArea;
}

QJsonObject NonogramFileWriter::serializePixel(Pixel pixel)
{
	QJsonObject jsonPixel;
	jsonPixel["sign"] = pixel.isDot() ? "dot" : (pixel.isFilledBlack() ? "fillBlack" : "empty");
	jsonPixel["addressX"] = static_cast<int>(pixel.getAddress().getX());
	jsonPixel["addressY"] = static_cast<int>(pixel.getAddress().getY());
	return jsonPixel;
}

QJsonArray NonogramFileWriter::serializeColumnsDescription()
{
	QJsonArray columnsDescription;
	for (size_t i = 0; i < field->getWidth(); i++)
	{
		columnsDescription.append(serializeLineDescription(i, AddressOnBlocksDescription::VERTICAL));
	}
	return columnsDescription;
}

QJsonArray NonogramFileWriter::serializeRowsDescription()
{
	QJsonArray rowsDescription;
	for (size_t i = 0; i < field->getHeight(); i++)
	{
		rowsDescription.append(serializeLineDescription(i, AddressOnBlocksDescription::HORIZONTAL));
	}
	return rowsDescription;
}

QJsonObject NonogramFileWriter::serializeLineDescription(size_t lineNumber, AddressOnBlocksDescription::orientation orientation)
{
	QJsonObject lineDescription;
	lineDescription["lineNumber"] = static_cast<int>(lineNumber);
	size_t lineLength;
	switch (orientation)
	{
	case AddressOnBlocksDescription::VERTICAL:
		lineLength = field->columnsDescription()->numberOfBlocksInLine(lineNumber);
		lineDescription["lineLength"] = static_cast<int>(lineLength);
		break;
	case AddressOnBlocksDescription::HORIZONTAL:
		lineLength = field->rowsDescription()->numberOfBlocksInLine(lineNumber);
		lineDescription["lineLength"] = static_cast<int>(lineLength);
		break;
	}
	lineDescription["lineDescription"] = serializeArrayOfBlockDescription(lineNumber, lineLength, orientation);

	return lineDescription;
	
}

QJsonArray NonogramFileWriter::serializeArrayOfBlockDescription(size_t lineNumber, size_t lineLength, AddressOnBlocksDescription::orientation orientation)
{
	QJsonArray arrayOfBlockDescription;
	for (size_t i = 0; i < lineLength; i++)
	{
		AddressOnBlocksDescription address = AddressOnBlocksDescription(orientation, lineNumber, i);
		arrayOfBlockDescription.append(serializeBlockDescription(address));
	}
	return arrayOfBlockDescription;
}

QJsonObject NonogramFileWriter::serializeBlockDescription(AddressOnBlocksDescription address)
{
	QJsonObject blockDescription;
	switch (address.getOrientation())
	{
	case AddressOnBlocksDescription::VERTICAL:
		blockDescription["blockSize"] = static_cast<int>(field->columnsDescription()->getBlockDescription(address).getBlockSize());
		blockDescription["count"] = static_cast<int>(address.getCount());
		blockDescription["isBlack"] = field->columnsDescription()->getBlockDescription(address).isFilledBlack();
		break;
	case AddressOnBlocksDescription::HORIZONTAL:
		blockDescription["blockSize"] = static_cast<int>(field->rowsDescription()->getBlockDescription(address).getBlockSize());
		blockDescription["count"] = static_cast<int>(address.getCount());
		blockDescription["isBlack"] = field->rowsDescription()->getBlockDescription(address).isFilledBlack();		
		break;
	}
	return blockDescription;
}

