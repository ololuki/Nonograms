#include "DrawingAreaController.h"

#include <QDebug>


DrawingAreaController::DrawingAreaController(std::shared_ptr<WholeField> newField, DrawingAreaView *drawingAreaView)
{
	qDebug() << "DrawingAreaController constructor";
	this->field = newField;
	this->drawingAreaView = drawingAreaView;
	drawingAreaView->setField(field);
	connect(drawingAreaView, &DrawingAreaView::mousePressed, this, &DrawingAreaController::onMouseButtonClicked);
}

DrawingAreaController::~DrawingAreaController()
{
	qDebug() << "DrawingAreaController destructor";
	disconnect(drawingAreaView, &DrawingAreaView::mousePressed, this, &DrawingAreaController::onMouseButtonClicked);
}

void DrawingAreaController::replaceField(std::shared_ptr<WholeField> newField)
{
	this->field = newField;
	drawingAreaView->setField(field);
}

void DrawingAreaController::onMouseButtonClicked(Qt::MouseButton mouseButton, AddressOnDrawingArea address)
{
	Pixel pixel(address);
	switch(mouseButton)
	{
	case Qt::LeftButton:
		pixel.makeFilledBlack();
		break;
	case Qt::RightButton:
		pixel.makeDot();
		break;
	case Qt::MiddleButton:
		pixel.makeEmpty();
		break;
	default:
		break;
	}
	field->setPixel(pixel);
}
