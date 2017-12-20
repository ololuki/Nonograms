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
	size["width"] = field->getWidth();
	size["height"] = field->getHeight();
	return size;
}

QJsonArray NonogramFileWriter::serializeDrawingArea()
{
	QJsonArray drawingArea;
	for (int y = 0; y < field->getHeight(); y++)
	{
		for (int x = 0; x < field->getWidth(); x++)
		{
			AddressOfCell address(x, y);
			Cell cell = field->cells()->getCell(address);
			drawingArea.append(serializeCell(cell));
		}
	}
	return drawingArea;
}

QJsonObject NonogramFileWriter::serializeCell(Cell cell)
{
	QJsonObject jsonCell;
	jsonCell["sign"] = cell.isDot() ? "dot" : (cell.isFilledBlack() ? "fillBlack" : "empty");
	jsonCell["addressX"] = cell.getAddress().getX();
	jsonCell["addressY"] = cell.getAddress().getY();
	return jsonCell;
}

QJsonArray NonogramFileWriter::serializeColumnsDescription()
{
	QJsonArray columnsDescription;
	for (int i = 0; i < field->getWidth(); i++)
	{
		columnsDescription.append(serializeLineDescription(i, Orientation::VERTICAL));
	}
	return columnsDescription;
}

QJsonArray NonogramFileWriter::serializeRowsDescription()
{
	QJsonArray rowsDescription;
	for (int i = 0; i < field->getHeight(); i++)
	{
		rowsDescription.append(serializeLineDescription(i, Orientation::HORIZONTAL));
	}
	return rowsDescription;
}

QJsonObject NonogramFileWriter::serializeLineDescription(int lineNumber, Orientation orientation)
{
	QJsonObject lineDescription;
	lineDescription["lineNumber"] = lineNumber;
	int lineLength;
	switch (orientation)
	{
	case Orientation::VERTICAL:
		lineLength = field->columnsHints()->numberOfBlocksInLine(lineNumber);
		lineDescription["lineLength"] = lineLength;
		break;
	case Orientation::HORIZONTAL:
		lineLength = field->rowsHints()->numberOfBlocksInLine(lineNumber);
		lineDescription["lineLength"] = lineLength;
		break;
	}
	lineDescription["lineDescription"] = serializeHintsInLine(lineNumber, lineLength, orientation);

	return lineDescription;
}

QJsonArray NonogramFileWriter::serializeHintsInLine(int lineNumber, int lineLength, Orientation orientation)
{
	QJsonArray lineOfHints;
	for (int i = 0; i < lineLength; i++)
	{
		AddressOfHint address = AddressOfHint(orientation, lineNumber, i);
		lineOfHints.append(serializeHint(address));
	}
	return lineOfHints;
}

QJsonObject NonogramFileWriter::serializeHint(AddressOfHint address)
{
	QJsonObject hint;
	switch (address.getOrientation())
	{
	case Orientation::VERTICAL:
		hint["blockSize"] = field->columnsHints()->getHint(address).getBlockSize();
		hint["count"] = address.getCount();
		hint["isBlack"] = field->columnsHints()->getHint(address).isFilledBlack();
		break;
	case Orientation::HORIZONTAL:
		hint["blockSize"] = field->rowsHints()->getHint(address).getBlockSize();
		hint["count"] = address.getCount();
		hint["isBlack"] = field->rowsHints()->getHint(address).isFilledBlack();
		break;
	}
	return hint;
}
