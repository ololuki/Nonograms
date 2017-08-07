#ifndef WHOLEFIELDIMPL_H
#define WHOLEFIELDIMPL_H

#include "WholeField.h"


///
/// \brief WholeFieldImpl class implementation - contains whole data about Field.
/// Constructor should invoke RootField(width, height) constructor.
///
class WholeFieldImpl : public WholeField
{
public:
	WholeFieldImpl(size_t width, size_t height);
	WholeFieldImpl(const WholeField &field);
	~WholeFieldImpl();
	virtual void clearDrawingArea() override;
	virtual void clearBlocksDescription() override;
};

#endif // WHOLEFIELDIMPL_H
