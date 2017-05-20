#ifndef LINEOFPIXELS_H
#define LINEOFPIXELS_H

#include "Pixel.h"
#include "vector"


///
/// \brief LineOfPixels stores one line of Pixels.
/// Orientation of the line (horizontal or vertical) is arbitrary.
/// Pixels are accesible by operator[].
///
class LineOfPixels : private std::vector<Pixel>
{
public:
	LineOfPixels() {}
	LineOfPixels(std::vector<Pixel> vectorToCopy) : std::vector<Pixel>(vectorToCopy) {}
	size_t size() {return std::vector<Pixel>::size();}
	
	Pixel& getPixelAt(const unsigned int pixelNumber) {return this->at(pixelNumber);}
	Pixel& operator[](const unsigned int pixelNumber) {return std::vector<Pixel>::operator[](pixelNumber);}
};

#endif // LINEOFPIXELS_H
