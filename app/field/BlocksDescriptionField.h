#ifndef BLOCKSDESCRIPTIONFIELD_H
#define BLOCKSDESCRIPTIONFIELD_H

#include "RootField.h"
#include "AddressOnBlocksDescription.h"
#include "BlockDescription.h"


///
/// \brief BlocksDescriptionField class is "interface" class 
/// to share data of Field with ColumnsDescriptionView and RowsDescriptionView.
/// It derives virtual from RootField because RootField is used in class DrawingAreaField too.
///
class BlocksDescriptionField : public virtual RootField
{
public:
	virtual BlockDescription getBlockDescription(AddressOnBlocksDescription address) = 0;
	virtual void updateBlockDescription(BlockDescription blockDescription) = 0;
	virtual void insertDescriptionBefore(BlockDescription blockDescription) = 0;
	virtual void addDescriptionAtEnd(BlockDescription blockDescription) = 0;
	virtual void deleteDescription(BlockDescription blockDescription) = 0;
	virtual size_t numberOfBlocksInColumn(size_t columnNumber) = 0;
	virtual size_t numberOfBlocksInRow(size_t rowNumber) = 0;
	virtual size_t columnsDescriptionHeight() = 0;
	virtual size_t rowsDescriptionWidth() = 0;
	virtual bool isDefinedColumnDescriptionAt(AddressOnBlocksDescription address) = 0;	
};

#endif // BLOCKSDESCRIPTIONFIELD_H
