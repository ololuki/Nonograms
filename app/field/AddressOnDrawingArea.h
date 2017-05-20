#ifndef ADDRESSONDRAWINGAREA_H
#define ADDRESSONDRAWINGAREA_H


///
/// \brief Contains address of every Pixel (box) on drawing area in Pixels (boxes)
///
class AddressOnDrawingArea
{
public:
	AddressOnDrawingArea(unsigned int x, unsigned int y) : x{x}, y(y) {}
	unsigned int getX() {return x;}
	unsigned int getY() {return y;}
	bool operator==(const AddressOnDrawingArea &address) const {
		return (this->x == address.x && this->y == address.y);
	}
private:
	unsigned int x;
	unsigned int y;
};

#endif // ADDRESSONDRAWINGAREA_H
