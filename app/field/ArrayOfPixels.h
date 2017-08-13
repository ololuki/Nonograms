#ifndef ARRAYOFPIXELS_H
#define ARRAYOFPIXELS_H

#include <vector>
#include "Pixel.h"


///
/// \brief ArrayOfPixels stores Pixels in 2-dimensional array.
/// Pixels are accesible by operator(), use (x, y)
/// Pixels are stored in vector of columns vector of Pixels to make sure
/// that in operator[] first [] will be for x (column number)
/// and second [] will be for y (row number)
///
class ArrayOfPixels : private std::vector<std::vector<Pixel>>
{
public:
	ArrayOfPixels() {}
	ArrayOfPixels(size_t width, size_t height)
	{
		for (size_t i = 0; i < width; i++)
		{
			this->push_back(std::vector<Pixel>());
			for (size_t j = 0; j < height; j++)
			{
				this->at(i).push_back(Pixel(AddressOnDrawingArea(i, j)));
			}
		}
	}
	Pixel& operator()(size_t x, size_t y)
	{
		return this->at(x)[y];
	}
	Pixel getPixelAt(size_t x, size_t y) const {
		return this->at(x).at(y);
	}
	int width() const;
	int height() const;
};

#endif // ARRAYOFPIXELS_H
