/**********************************************************************
 * Copyright (C) 2017 - 2021 Ololuki
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
#ifndef HINTSCONTROLLER_H
#define HINTSCONTROLLER_H

#include "action/HintAction.h"
#include "field/AddressOfHint.h"
#include "field/Hint.h"
#include <QObject>
#include <memory>

class HintsFieldModel;
class HintsView;


class HintsController : public QObject
{
	Q_OBJECT
public:
	HintsController(std::shared_ptr<HintsFieldModel> field, HintsView *hintsView);
	~HintsController() override = default;

signals:
	// invoked by controller
	void showInsertingButtonBefore(AddressOfHint address);
	void showHintEditingBox(AddressOfHint address);

private slots:
	// on signals emited to controller
	void onAction(HintAction action, AddressOfHint address);
	void onAction(HintAction action, Hint hint);

private:
	// when inserting button is clicked
	void onHintInsertBefore(AddressOfHint address);

	std::shared_ptr<HintsFieldModel> field;
	HintsView *hintsView;
};

#endif // HINTSCONTROLLER_H
