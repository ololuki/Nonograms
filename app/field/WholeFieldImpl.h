#ifndef WHOLEFIELDIMPL_H
#define WHOLEFIELDIMPL_H

#include "WholeField.h"
#include "ArrayOfPixels.h"

///
/// \brief WholeFieldImpl class implementation - contains whole data about Field.
/// Constructor should invoke RootField(width, height) constructor.
///
class WholeFieldImpl : public WholeField
{
public:
	WholeFieldImpl(int width, int height) : RootField(width, height) {array = ArrayOfPixels(width, height);}
	virtual Pixel getPixel(AddressOnDrawingArea address) override;
	virtual void setPixel(Pixel pixel) override;
private:
	ArrayOfPixels array;
};

#endif // WHOLEFIELDIMPL_H
