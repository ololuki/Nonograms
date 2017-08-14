#include "WholeField.h"
#include <QDebug>


WholeField::WholeField(size_t width, size_t height)
	: BlocksDescriptionField (width, height)
{
	drawingAreaField = std::make_shared<DrawingAreaField>(width, height);
	columnsDescription = AllLinesDescription(AddressOnBlocksDescription::VERTICAL, width);
	rowsDescription = AllLinesDescription(AddressOnBlocksDescription::HORIZONTAL, height);
	qDebug() << "WholeField width height c-tor";
}

WholeField::WholeField(const WholeField &field)
	: BlocksDescriptionField(field.getWidth(), field.getHeight())
{
	drawingAreaField = field.drawingAreaField;
	columnsDescription = field.columnsDescription;
	rowsDescription = field.rowsDescription;
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
