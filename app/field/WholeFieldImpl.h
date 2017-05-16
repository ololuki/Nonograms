#ifndef WHOLEFIELDIMPL_H
#define WHOLEFIELDIMPL_H

#include "WholeField.h"


///
/// \brief WholeFieldImpl class implementation - contains whole data about Field.
/// Constructor should invoke RootField(width, height) constructor.
///
class WholeFieldImpl : public WholeField
{
public:
	WholeFieldImpl(int width, int height) : RootField(width, height) {}
	virtual Pixel getPixel(AddressOnDrawingArea address) override;
	virtual void setPixel(Pixel pixel) override;
};

#endif // WHOLEFIELDIMPL_H
