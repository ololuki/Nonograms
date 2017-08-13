#ifndef DRAWINGAREAFIELD_H
#define DRAWINGAREAFIELD_H

#include <QObject>
#include "RootField.h"
#include "AddressOnDrawingArea.h"
#include "Pixel.h"
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
	virtual Pixel getPixel(AddressOnDrawingArea address) const;
	virtual void setPixel(Pixel pixel);
signals:
	void pixelChanged(AddressOnDrawingArea address);
protected:
	ArrayOfPixels array;
};

#endif // DRAWINGAREAFIELD_H
