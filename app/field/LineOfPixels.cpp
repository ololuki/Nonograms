#include "LineOfPixels.h"

LineOfPixels::LineOfPixels(std::vector<Pixel> vectorToCopy)
{
	pixels = vectorToCopy;
}

int LineOfPixels::size()
{
	return static_cast<int>(pixels.size());
}

Pixel &LineOfPixels::getPixelAt(const int pixelNumber)
{
	return pixels.operator[](static_cast<size_t>(pixelNumber));
}

Pixel &LineOfPixels::operator[](const int pixelNumber)
{
	return pixels.operator[](static_cast<size_t>(pixelNumber));
}
