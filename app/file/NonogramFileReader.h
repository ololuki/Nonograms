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
#ifndef NONOGRAMFILEREADER_H
#define NONOGRAMFILEREADER_H

#include "file/FileReader.h"
#include <QJsonObject>
#include <QJsonArray>

#include "field/Pixel.h"


///
/// Reading from file and parsing JSON to whole field
///
class NonogramFileReader : public FileReader
{
public:
	NonogramFileReader();
	~NonogramFileReader();
	
	std::shared_ptr<WholeField> getField() override;
	bool read(const std::string &fileDir) override;
	
private:
	std::shared_ptr<WholeField> field;
	
	void parseSize(int &width, int &height, QJsonObject jsonSize);
	void parseDrawingArea(QJsonArray drawingArea);
	Pixel parsePixel(QJsonObject jsonPixel);
	
	void parseColumnsDescription(QJsonArray columnsDescription);
	void parseRowsDescription(QJsonArray rowsDescription);
	void parseLineDescription(QJsonObject jsonLineDescription, int lineNumber, AddressOnBlocksDescription::orientation orientation);
	void parseArrayOfBlockDescription(QJsonArray jsonArray, int lineNumber, int lineLength, AddressOnBlocksDescription::orientation orientation);
	void parseBlockDescription(QJsonObject jsonBlockDescription, AddressOnBlocksDescription address);
};

#endif // NONOGRAMFILEREADER_H
