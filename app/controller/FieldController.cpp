#include "FieldController.h"
#include "field/WholeFieldImpl.h"
#include "SizeDialog.h"
#include <QDebug>


FieldController::FieldController(DrawingAreaView *drawingAreaView, ColumnsDescriptionView *columnsDescriptionView, RowsDescriptionView *rowsDescriptionView)
{
	// create initial field
	field.reset(new WholeFieldImpl(14, 10));
	
	this->drawingAreaView = drawingAreaView;
	drawingAreaController = std::make_shared<DrawingAreaController>(field->drawingArea(), drawingAreaView);
	
	this->columnsDescriptionView = columnsDescriptionView;
	columnsDescriptionView->setField(field);
	
	this->rowsDescriptionView = rowsDescriptionView;
	rowsDescriptionView->setField(field);
	
	fileController = std::make_shared<FileController>(field);
}

void FieldController::addDummyBlock()
{
	if (field->getWidth() < 3 || field->getHeight() < 8) return;
	field->drawingArea()->setPixel(Pixel(AddressOnDrawingArea(2,5), pixelSign::SGN_FILL_BLACK));
	field->drawingArea()->setPixel(Pixel(AddressOnDrawingArea(2,7), pixelSign::SGN_FILL_BLACK));
	field->updateBlockDescription(BlockDescription(AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, 2, 0), 1));
	field->addDescriptionAtEnd(BlockDescription(AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, 2, 1), 1));
	field->updateBlockDescription(BlockDescription(AddressOnBlocksDescription(AddressOnBlocksDescription::HORIZONTAL, 5, 0), 1));
	field->updateBlockDescription(BlockDescription(AddressOnBlocksDescription(AddressOnBlocksDescription::HORIZONTAL, 7, 0), 1));
}

void FieldController::recreateField(size_t width, size_t height)
{
	field.reset(new WholeFieldImpl(width, height));
	drawingAreaController->replaceField(field->drawingArea());
	columnsDescriptionView->setField(field);
	rowsDescriptionView->setField(field);
}

void FieldController::replaceField(std::shared_ptr<WholeField> newField)
{
	if (newField == nullptr)
	{
		qDebug() << "null ptr";
		return;
	}
	field = newField;
	
	drawingAreaController->replaceField(field->drawingArea());
	
	columnsDescriptionView->setField(field);
	rowsDescriptionView->setField(field);
}

void FieldController::onNew()
{
	if (!fileController->abandonChangesOrSavePrompt(field)) return;
	//fileController->tryToSaveChanges(&isSavedOrAbandoned, &statusLog);
	//if (!isSavedOrAbandoned) return;
	
	SizeDialog *d = new SizeDialog();
	bool isConfirmed = d->exec();
	size_t width = d->getWidth();
	size_t height = d->getHeight();
	delete d;
	if (isConfirmed)
	{
		recreateField(width, height);
		fileController->setNewCreatedField(field);
	}
}

void FieldController::onOpen()
{
	if (!fileController->abandonChangesOrSavePrompt(field)) return;
	fileController->tryOpenAnotherFile();
	replaceField(fileController->getField());
}

void FieldController::onSaveAs()
{
	fileController->trySaveAs(field);
}
