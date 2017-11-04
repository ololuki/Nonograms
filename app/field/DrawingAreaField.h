#ifndef DRAWINGAREAFIELD_H
#define DRAWINGAREAFIELD_H

#include <QObject>
#include "AddressOfCell.h"
#include "Cell.h"
#include "ArrayOfPixels.h"


///
/// \brief DrawingAreaField class is model class of drawing area data.
/// DrawingAreaField is part of WholeField. WholeField contains DrawingAreaField.
///
class DrawingAreaField : public QObject
{
	Q_OBJECT
public:
	DrawingAreaField(int width, int height);
	~DrawingAreaField();
	int getWidth() const {return array.width();}
	int getHeight() const {return array.height();}
	virtual Cell getCell(AddressOfCell address) const;
	virtual void setCell(Cell cell);
signals:
	void cellChanged(AddressOfCell address);
protected:
	ArrayOfPixels array;
};

#endif // DRAWINGAREAFIELD_H
