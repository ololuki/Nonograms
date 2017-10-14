#include "ArrayOfPixels.h"

int ArrayOfPixels::width() const
{
	return static_cast<int>(size());
}

int ArrayOfPixels::height() const
{
	if (size() == 0) return 0;
	return static_cast<int>(at(0).size());
}
