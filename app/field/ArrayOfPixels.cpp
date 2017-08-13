#include "ArrayOfPixels.h"

int ArrayOfPixels::width() const
{
	return size();
}

int ArrayOfPixels::height() const
{
	if (size() == 0) return 0;
	return (at(0).size());
}
