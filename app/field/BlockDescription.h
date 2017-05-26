#ifndef BLOCKDESCRIPTION_H
#define BLOCKDESCRIPTION_H

#include "AddressOnBlocksDescription.h"
#include "pixelSign.h"


///
/// \brief BlockDescription class contains one block description (number) of picture (field). 
/// Sign is for future use - every block is currently black.
///
class BlockDescription
{
public:
	BlockDescription(AddressOnBlocksDescription address, size_t blockSize, pixelSign sign = pixelSign::SGN_FILL_BLACK) 
		: address(address), blockSize(blockSize), sign(sign) {}
	size_t getBlockSize() {return blockSize;}
	void setBlockSize(size_t blockSize) {this->blockSize = blockSize;}
	bool isFilledBlack(){return sign == pixelSign::SGN_FILL_BLACK;}
	void makeFilledBlack() {sign = pixelSign::SGN_FILL_BLACK;}
	AddressOnBlocksDescription getAddress() {return address;}
private:
	AddressOnBlocksDescription address;
	size_t blockSize;
	pixelSign sign;
};

#endif // BLOCKDESCRIPTION_H
