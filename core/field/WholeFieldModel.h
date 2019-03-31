/**********************************************************************
 * Copyright (C) 2017 - 2019 Ololuki
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
#ifndef WHOLEFIELDMODEL_H
#define WHOLEFIELDMODEL_H

#include <memory>
#include "CellsFieldModel.h"
#include "HintsFieldModel.h"
#include "WholeField.h"
#include <QMetaType>


///
/// \brief WholeFieldModel class contains Field models.
/// It has models of field parts: drawing area, columns hints
/// and rows hints.
///
class WholeFieldModel
{
public:
	WholeFieldModel(int width, int height);
	WholeFieldModel(const WholeFieldModel &field);
	virtual ~WholeFieldModel();
	int getWidth() const;
	int getHeight() const;
	std::shared_ptr<CellsFieldModel> cells();
	std::shared_ptr<HintsFieldModel> columnsHints();
	std::shared_ptr<HintsFieldModel> rowsHints();
	void clearDrawingArea();
	void clearBlocksDescription();

	WholeField getWholeField();
	void setWholeField(WholeField field);
private:
	int width;
	int height;
	std::shared_ptr<CellsFieldModel> cellsField;
	std::shared_ptr<HintsFieldModel> columnsHintsField;
	std::shared_ptr<HintsFieldModel> rowsHintsField;
};

Q_DECLARE_METATYPE(std::shared_ptr</*const*/ WholeFieldModel>)

#endif // WHOLEFIELDMODEL_H
