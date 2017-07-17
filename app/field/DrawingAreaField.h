#ifndef DRAWINGAREAFIELD_H
#define DRAWINGAREAFIELD_H

#include <QObject>
#include "RootField.h"
#include "AddressOnDrawingArea.h"
#include "Pixel.h"
#include "ArrayOfPixels.h"


///
/// \brief DrawingAreaField class is "interface" class to share data of Field with DrawingAreaView.
/// It derives virtual from RootField because RootField is used in class BlocksDescriptionField too.
///
class DrawingAreaField : public QObject, public virtual RootField
{
	Q_OBJECT
public:
	virtual Pixel getPixel(AddressOnDrawingArea address);
	virtual void setPixel(Pixel pixel);
signals:
	void pixelChanged(AddressOnDrawingArea address);
protected:
	ArrayOfPixels array;
};

#endif // DRAWINGAREAFIELD_H
