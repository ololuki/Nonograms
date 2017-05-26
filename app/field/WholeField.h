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
};

#endif // WHOLEFIELD_H
