#ifndef ADDRESSONDRAWINGAREA_H
#define ADDRESSONDRAWINGAREA_H


///
/// \brief Contains address of every Pixel (box) on drawing area in Pixels (boxes)
///
class AddressOnDrawingArea
{
public:
	AddressOnDrawingArea(size_t x, size_t y) : x(x), y(y) {}
	size_t getX() {return x;}
	size_t getY() {return y;}
	bool operator==(const AddressOnDrawingArea &address) const {
		return (this->x == address.x && this->y == address.y);
	}
private:
	size_t x;
	size_t y;
};

#endif // ADDRESSONDRAWINGAREA_H
