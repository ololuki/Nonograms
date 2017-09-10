#ifndef DRAWINGAREACONTROLLER_H
#define DRAWINGAREACONTROLLER_H

#include "field/WholeField.h"
#include "widgets/DrawingAreaView.h"


class DrawingAreaController : public QObject
{
	Q_OBJECT
public:
	DrawingAreaController(std::shared_ptr<DrawingAreaField> newField, DrawingAreaView *drawingAreaView);
	~DrawingAreaController();
	void replaceField(std::shared_ptr<DrawingAreaField> newField);
private slots:
	void onMouseButtonClicked(Qt::MouseButton mouseButton, AddressOnDrawingArea address);
protected:
	std::shared_ptr<DrawingAreaField> field;
private:
	DrawingAreaView *drawingAreaView;
};

#endif // DRAWINGAREACONTROLLER_H