#ifndef FIELDCONTROLLER_H
#define FIELDCONTROLLER_H

#include "field/WholeField.h"
#include "widgets/DrawingAreaView.h"
#include "widgets/ColumnsDescriptionView.h"
#include "widgets/RowsDescriptionView.h"
#include "controller/DrawingAreaController.h"
#include "controller/FileController.h"


class FieldController : public QObject
{
	Q_OBJECT
public:
	FieldController(DrawingAreaView *drawingAreaView, ColumnsDescriptionView *columnsDescriptionView, RowsDescriptionView *rowsDescriptionView);
	void addDummyBlock();
	
	void onNew();
	void onOpen();
	void onSaveAs();
private:
	void recreateField(size_t width, size_t height);
	void replaceField(std::shared_ptr<WholeField> newField);
	
	std::shared_ptr<WholeField> field;
	
	DrawingAreaView *drawingAreaView;
	ColumnsDescriptionView *columnsDescriptionView;
	RowsDescriptionView *rowsDescriptionView;
	
	std::shared_ptr<DrawingAreaController> drawingAreaController;
	std::shared_ptr<FileController> fileController;
};

#endif // FIELDCONTROLLER_H
