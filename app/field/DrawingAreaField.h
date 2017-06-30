#ifndef DRAWINGAREAFIELD_H
#define DRAWINGAREAFIELD_H

#include "RootField.h"
#include "AddressOnDrawingArea.h"
#include "Pixel.h"


///
/// \brief DrawingAreaField class is "interface" class to share data of Field with DrawingAreaView.
/// It derives virtual from RootField because RootField is used in class BlocksDescriptionField too.
///
class DrawingAreaField : public virtual RootField, public QObject
{
	Q_OBJECT
public:
	virtual Pixel getPixel(AddressOnDrawingArea address) = 0;
	virtual void setPixel(Pixel pixel) = 0;
signals:
	void pixelChanged(AddressOnDrawingArea address);
};

#endif // DRAWINGAREAFIELD_H
