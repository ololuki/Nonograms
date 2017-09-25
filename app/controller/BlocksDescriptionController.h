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
#ifndef BLOCKSDESCRIPTIONCONTROLLER_H
#define BLOCKSDESCRIPTIONCONTROLLER_H

#include <QObject>
#include "field/AddressOnBlocksDescription.h"
#include "field/BlockDescription.h"
#include <memory>
#include "widgets/HintsView.h"


class BlocksDescriptionController : public QObject
{
	Q_OBJECT
public:
	BlocksDescriptionController(std::shared_ptr<BlocksDescriptionField> field, HintsView *hintsView);
	~BlocksDescriptionController();
	
signals:
	// invoked by controller
	void showInsertingButtonBefore(AddressOnBlocksDescription address);
	// invoked by controller
	void showDescriptionEditingBox(AddressOnBlocksDescription address);
	
private slots:
	// on signals emited to controller
	// when cursor starts being on the potential inserting button area
	void onInsertingButtonHover(AddressOnBlocksDescription address);
	// when editing description ends
	void onDescriptionEditingFinished(BlockDescription blockDescription);
	// when inserting button is clicked
	void onInsertingButtonBeforeAddressClicked(AddressOnBlocksDescription address);
	void onBlockDescriptionClicked(AddressOnBlocksDescription address);
	
};

#endif // BLOCKSDESCRIPTIONCONTROLLER_H
