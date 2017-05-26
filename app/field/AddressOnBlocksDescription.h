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
	
	AddressOnBlocksDescription(AddressOnBlocksDescription::orientation o, size_t line, size_t count);
	size_t getLine() {return line;}
	size_t getCount() {return count;}
	bool isColumn() {return o == VERTICAL;}
	bool isRow() {return o == HORIZONTAL;}
	
private:
	orientation o;
	size_t line;
	size_t count;
};

#endif // ADDRESSONBLOCKSDESCRIPTION_H
