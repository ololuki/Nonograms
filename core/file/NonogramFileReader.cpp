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
#include "field/WholeFieldModel.h"


NonogramFileReader::NonogramFileReader()
{
	
}

NonogramFileReader::~NonogramFileReader()
{
	
}

WholeField NonogramFileReader::getField()
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
	int width;
	int height;
	parseSize(width, height, jsonSize);
	field = WholeField(width, height);
	QJsonArray drawingArea = jsonObj["drawingArea"].toArray();
	parseDrawingArea(drawingArea);
	
	QJsonArray columnsDescription = jsonObj["columnsDescription"].toArray();
	parseColumnsDescription(columnsDescription);
	
	QJsonArray rowsDescription = jsonObj["rowsDescription"].toArray();
	parseRowsDescription(rowsDescription);
	
	return true;
}

void NonogramFileReader::parseSize(int &width, int &height, QJsonObject jsonSize)
{
	width = static_cast<size_t>(jsonSize["width"].toInt());
	height = static_cast<size_t>(jsonSize["height"].toInt());
}

void NonogramFileReader::parseDrawingArea(QJsonArray drawingArea)
{
	for(int i = 0; i < drawingArea.size(); i++)
	{
		QJsonObject jsonCell = drawingArea[i].toObject();
		Cell cell = parseCell(jsonCell);
		field.cells().setCell(cell);
	}
}

Cell NonogramFileReader::parseCell(QJsonObject jsonCell)
{
	int addressX = jsonCell["addressX"].toInt();
	int addressY = jsonCell["addressY"].toInt();
	AddressOfCell address(addressX, addressY);
	Cell cell = Cell(address);
	if (jsonCell["sign"].toString() == "empty") cell.makeEmpty();
	else if (jsonCell["sign"].toString() == "dot") cell.makeDot();
	else if (jsonCell["sign"].toString() == "fillBlack") cell.makeFilledBlack();
	return cell;
}

void NonogramFileReader::parseColumnsDescription(QJsonArray columnsDescription)
{
	for (int i = 0; i < columnsDescription.size(); i++)
	{
		QJsonObject jsonLineDescription = columnsDescription[i].toObject();
		parseLineDescription(jsonLineDescription, i, Orientation::VERTICAL);
	}
}

void NonogramFileReader::parseRowsDescription(QJsonArray rowsDescription)
{
	for (int i = 0; i < rowsDescription.size(); i++)
	{
		QJsonObject jsonLineDescription = rowsDescription[i].toObject();
		parseLineDescription(jsonLineDescription, i, Orientation::HORIZONTAL);
	}
}

void NonogramFileReader::parseLineDescription(QJsonObject jsonLineDescription, int lineNumber, Orientation orientation)
{
	int lineLength = jsonLineDescription["lineLength"].toInt();
	QJsonArray jsonLineOfHints = jsonLineDescription["lineDescription"].toArray();
	parseHintsInLine(jsonLineOfHints, lineNumber, lineLength, orientation);
	switch (orientation)
	{
	case Orientation::VERTICAL:
		field.columnsHints().deleteHint(Hint(AddressOfHint(orientation, lineNumber, lineLength), 0));
		break;
	case Orientation::HORIZONTAL:
		field.rowsHints().deleteHint(Hint(AddressOfHint(orientation, lineNumber, lineLength), 0));
		break;
	}
}

void NonogramFileReader::parseHintsInLine(QJsonArray jsonLineOfHints, int lineNumber, int lineLength, Orientation orientation)
{
	for (int i = 0; i < lineLength; i++)
	{
		AddressOfHint address = AddressOfHint(orientation, lineNumber, i);
		QJsonObject jsonHint = jsonLineOfHints[i].toObject();
		parseHint(jsonHint, address);
	}
}

void NonogramFileReader::parseHint(QJsonObject jsonHint, AddressOfHint address)
{
	int blockSize = jsonHint["blockSize"].toInt();
	switch (address.getOrientation())
	{
	case Orientation::VERTICAL:
		field.columnsHints().insertHintBefore(Hint(address, blockSize));
		break;
	case Orientation::HORIZONTAL:
		field.rowsHints().insertHintBefore(Hint(address, blockSize));
		break;
	}
}
