#ifndef BLOCKSDESCRIPTIONFIELD_H
#define BLOCKSDESCRIPTIONFIELD_H

#include <QObject>
#include "RootField.h"
#include "AddressOnBlocksDescription.h"
#include "BlockDescription.h"
#include "AllLinesDescription.h"


///
/// \brief BlocksDescriptionField class is "interface" class 
/// to share data of Field with ColumnsDescriptionView and RowsDescriptionView.
/// It derives virtual from RootField because RootField is used in class DrawingAreaField too.
///
class BlocksDescriptionField : public QObject, public virtual RootField
{
	Q_OBJECT
public:
	virtual BlockDescription getBlockDescription(AddressOnBlocksDescription address);
	virtual void updateBlockDescription(BlockDescription blockDescription);
	virtual void insertDescriptionBefore(BlockDescription blockDescription);
	virtual void addDescriptionAtEnd(BlockDescription blockDescription);
	virtual void deleteDescription(BlockDescription blockDescription);
	virtual size_t numberOfBlocksInColumn(size_t columnNumber);
	virtual size_t numberOfBlocksInRow(size_t rowNumber);
	virtual size_t columnsDescriptionHeight();
	virtual size_t rowsDescriptionWidth();
	virtual bool isDefinedColumnDescriptionAt(AddressOnBlocksDescription address);
signals:
	void blocksDescriptionChanged();
protected:
	AllLinesDescription columnsDescription;
	AllLinesDescription rowsDescription;
};

#endif // BLOCKSDESCRIPTIONFIELD_H
