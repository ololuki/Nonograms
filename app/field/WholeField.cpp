#include "WholeField.h"
#include <QDebug>


WholeField::WholeField(size_t width, size_t height)
{
	drawingAreaField = std::make_shared<DrawingAreaField>(width, height);
	qDebug() << "WholeField width height c-tor";
}

WholeField::WholeField(const WholeField &field)
{
	drawingAreaField = field.drawingAreaField;
	qDebug() << "WholeField copy c-tor";
}

WholeField::~WholeField()
{
	qDebug() << "WholeField d-tor";
}

std::shared_ptr<DrawingAreaField> WholeField::drawingArea()
{
	return drawingAreaField;
}
