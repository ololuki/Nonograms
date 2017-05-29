#ifndef WHOLEFIELDIMPL_H
#define WHOLEFIELDIMPL_H

#include "WholeField.h"
#include "ArrayOfPixels.h"
#include "AllLinesDescription.h"


///
/// \brief WholeFieldImpl class implementation - contains whole data about Field.
/// Constructor should invoke RootField(width, height) constructor.
///
class WholeFieldImpl : public WholeField
{
public:
	WholeFieldImpl(size_t width, size_t height);
	virtual Pixel getPixel(AddressOnDrawingArea address) override;
	virtual void setPixel(Pixel pixel) override;
	virtual BlockDescription getBlockDescription(AddressOnBlocksDescription address) override;
	virtual void updateBlockDescription(BlockDescription blockDescription) override;
	virtual void insertDescriptionBefore(BlockDescription blockDescription) override;
	virtual void addDescriptionAtEnd(BlockDescription blockDescription) override;
	virtual void deleteDescription(BlockDescription blockDescription) override;
	virtual size_t numberOfBlocksInColumn(size_t columnNumber) override;
	virtual size_t numberOfBlocksInRow(size_t rowNumber) override;
	virtual size_t columnsDescriptionHeight() override;
	virtual size_t rowsDescriptionWidth() override;
	virtual bool isDefinedColumnDescriptionAt(AddressOnBlocksDescription address) override;
private:
	ArrayOfPixels array;
	AllLinesDescription columnsDescription;
	AllLinesDescription rowsDescription;
};

#endif // WHOLEFIELDIMPL_H
