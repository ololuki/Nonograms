#ifndef ADDRESSONBLOCKSDESCRIPTION_H
#define ADDRESSONBLOCKSDESCRIPTION_H

///
/// \brief Contains address of every Block Description (number) on BlocksDescriptionField
/// address counts from top do bottom
/// and from left to right
///
class AddressOnBlocksDescription
{
public:
	enum orientation
	{
		HORIZONTAL,
		VERTICAL,
	};
	
	AddressOnBlocksDescription(orientation o, size_t line, size_t count);
	size_t getLine() {return line;}
	size_t getCount() {return count;}
	orientation getOrientation() {return o;}
	bool isColumn() {return o == VERTICAL;}
	bool isRow() {return o == HORIZONTAL;}
	bool operator==(const AddressOnBlocksDescription &address) const {
		return (this->line == address.line && this->count == address.count && this->o == address.o);
	}
private:
	orientation o;
	size_t line;
	size_t count;
};

#endif // ADDRESSONBLOCKSDESCRIPTION_H
