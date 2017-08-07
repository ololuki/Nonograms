#ifndef WHOLEFIELD_H
#define WHOLEFIELD_H

#include "DrawingAreaField.h"
#include "BlocksDescriptionField.h"


///
/// \brief WholeField class is "interface" that contains whole data about Field.
/// You should invoke RootField(width, height) constructor in child class constructor
///
class WholeField : public DrawingAreaField, public BlocksDescriptionField, virtual public RootField
{
	friend class WholeFieldImpl;	// for copy c-tor
public:
	virtual ~WholeField();
	virtual void clearDrawingArea() = 0;
	virtual void clearBlocksDescription() = 0;
};

#endif // WHOLEFIELD_H
