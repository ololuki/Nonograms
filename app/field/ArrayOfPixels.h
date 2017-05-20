#ifndef ARRAYOFPIXELS_H
#define ARRAYOFPIXELS_H

#include <vector>
#include "Pixel.h"


///
/// \brief ArrayOfPixels stores Pixels in 2-dimensional array.
/// Pixels are accesible by operator[], use array[x][y]
/// Pixels are stored in vector of columns vector of Pixels to make sure
/// that in operator[] first [] will be for x (column number)
/// and second [] will be for y (row number)
///
class ArrayOfPixels : private std::vector<std::vector<Pixel>>
{
public:
	ArrayOfPixels() {}
	ArrayOfPixels(unsigned int width, unsigned int height)
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
	std::vector<Pixel> & operator[](unsigned int i) 
	{ 
		return this->at(i);
	}
	const std::vector<Pixel> & operator[] (unsigned int i) const 
	{ 
		return this->at(i);
	}
	// getPixelAt(x, y) 
};

#endif // ARRAYOFPIXELS_H
