#ifndef PIXEL_H
#define PIXEL_H

#include "AddressOnDrawingArea.h"
#include "pixelSign.h"


///
/// \brief Pixel class contains one pixel (box) of picture (field). It has address in pixels (boxes) and sign to draw
///
class Pixel
{
public:
	Pixel(pixelSign sign, AddressOnDrawingArea address) : sign(sign), address(address) {}
	bool isFilledBlack(){return sign == pixelSign::SGN_FILL_BLACK;}
	bool isDot(){return sign == pixelSign::SGN_DOT;}
	bool isEmpty(){return sign == pixelSign::SGN_EMPTY;}
	AddressOnDrawingArea getAddress() {return address;}
private:
	AddressOnDrawingArea address;
	pixelSign sign;
};

#endif // PIXEL_H
