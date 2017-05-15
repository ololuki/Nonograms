#ifndef PIXELSIGN_H
#define PIXELSIGN_H


///
/// \brief pixelSign class enum contains available signs for pixels of picture
///
enum class pixelSign
{
	SGN_EMPTY = -1,			// '-' unresolved
	SGN_FILLED = -2,		// '#' filled pixel (not used, filled black will be used)
	SGN_DOT = -3,			// '.' pixel with no block (white)
	SGN_FILL_BLACK = -4,	// '#' filled with black color
	// numbers 0 to max-int will be used by solver to name pixels by number of current block
};

#endif // PIXELSIGN_H
