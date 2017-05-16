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
	Pixel(AddressOnDrawingArea address, pixelSign sign = pixelSign::SGN_EMPTY) : address(address), sign(sign) {}
	bool isFilledBlack(){return sign == pixelSign::SGN_FILL_BLACK;}
	bool isDot(){return sign == pixelSign::SGN_DOT;}
	bool isEmpty(){return sign == pixelSign::SGN_EMPTY;}
	void makeFilledBlack() {sign = pixelSign::SGN_FILL_BLACK;}
	void makeDot(){sign = pixelSign::SGN_DOT;}
	void makeEmpty(){sign = pixelSign::SGN_EMPTY;}
	AddressOnDrawingArea getAddress() {return address;}
private:
	AddressOnDrawingArea address;
	pixelSign sign;
};

#endif // PIXEL_H
