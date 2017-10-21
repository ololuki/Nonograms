#ifndef LINEOFPIXELS_H
#define LINEOFPIXELS_H

#include "Pixel.h"
#include "vector"
#include "utils/NVector.h"


///
/// \brief LineOfPixels stores one line of Pixels.
/// Orientation of the line (horizontal or vertical) is arbitrary.
/// Pixels are accesible by operator[].
///
class LineOfPixels
{
public:
	LineOfPixels(NVector<Pixel> vectorToCopy);
	int size();
	
	Pixel& getPixelAt(const int pixelNumber);
	Pixel& operator[](const int pixelNumber);
private:
	NVector<Pixel> pixels;
};

#endif // LINEOFPIXELS_H
