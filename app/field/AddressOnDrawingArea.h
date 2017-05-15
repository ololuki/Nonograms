#ifndef ADDRESSONDRAWINGAREA_H
#define ADDRESSONDRAWINGAREA_H


///
/// \brief Contains address of every Pixel (box) on drawing area in Pixels (boxes)
///
class AddressOnDrawingArea
{
public:
	AddressOnDrawingArea(int x, int y) : x(x), y(y) {}
	int getX() {return x;}
	int getY() {return y;}
private:
	int x;
	int y;
};

#endif // ADDRESSONDRAWINGAREA_H
