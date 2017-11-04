#include "DrawingAreaField.h"
#include <QDebug>


DrawingAreaField::DrawingAreaField(int width, int height) : array(width, height)
{
	qDebug() << "DrawingAreaField width height c-tor";
}

DrawingAreaField::~DrawingAreaField()
{
	qDebug() << "DrawingAreaField d-tor";
}

Cell DrawingAreaField::getCell(AddressOfCell address) const
{
	int x = address.getX();
	int y = address.getY();
	return array.getPixelAt(x, y);
}

void DrawingAreaField::setCell(Cell cell)
{
	int x = cell.getAddress().getX();
	int y = cell.getAddress().getY();
	array(x, y) = cell;
	emit cellChanged(cell.getAddress());
}
