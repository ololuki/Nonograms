#ifndef ROOTFIELD_H
#define ROOTFIELD_H

#include <QObject>


///
/// \brief RootField class is a base class that contains common parameters for whole Field (width and height).
/// You should init this class with constructor RootField(int width, int height).
/// Signal dataChanged() should be invoked every time any data is changed inside classes that deriving from this.
///
class RootField : public QObject
{
	Q_OBJECT
public:
	RootField();
	RootField(int width, int height) : width(width), height(height) {}
	int getWidth() {return width;}
	int getHeight() {return height;}
signals:
	void dataChanged();
private:
	int width;
	int height;
};

#endif // ROOTFIELD_H
