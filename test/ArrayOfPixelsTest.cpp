#include "catch.hpp"
#include "../app/field/ArrayOfPixels.h"


TEST_CASE("ArrayOfPixels") {
	unsigned int x = 2;
	unsigned int y = x + 1;
	ArrayOfPixels array(x, y);
			
	SECTION( "operator(x, y) should return reference to Cell" ) {
		Cell &cell = array(0, 0);
		REQUIRE( array(0, 0).isDot() == false );
		cell.makeDot();
		REQUIRE( array(0, 0).isDot() == true );
	}
	
	SECTION( "assigning cell object to Cell& referenced by operator() (array(x, y)) should work" ) {
		Cell cell = Cell(AddressOfCell(0, 0));
		cell.makeEmpty();
		array(0, 0) = cell;
		REQUIRE( array(0, 0).isEmpty() );
		cell.makeDot();
		array(0, 0) = cell;
		REQUIRE( array(0, 0).isDot() );
	}
	
	SECTION( "assigning cell object to Cell& referenced by operator() (array(x, y)) should be by value, NOT reference" ) {
		Cell cell = Cell(AddressOfCell(0, 0));
		cell.makeEmpty();
		array(0, 0) = cell;
		REQUIRE( array(0, 0).isEmpty() );
		cell.makeDot();
		REQUIRE( array(0, 0).isEmpty() );
	}
	
	SECTION( "operator(x, y) should return Cell with suitable Address" ) {
		REQUIRE( array(0, 0).getAddress() == AddressOfCell(0, 0) );
		REQUIRE( array(0, 1).getAddress() == AddressOfCell(0, 1) );
		REQUIRE( array(1, 0).getAddress() == AddressOfCell(1, 0) );
	}
	
	SECTION( "order of ctor arguments should be same as order of operator(), eg. array(x, y) <=> ArrayOfPixels(x, y)" ) {
		REQUIRE( array(x-1, y-1).getAddress() == AddressOfCell(x-1, y-1) );
	}
	
	SECTION( "width() and height() should return width and height of array" ) {
		REQUIRE( array.width() == x );
		REQUIRE( array.height() == y );
	}
	
	SECTION( "width() and height() for empty array should return 0 and 0" ) {
		ArrayOfPixels emptyArray(0, 0);
		REQUIRE( emptyArray.width() == 0 );
		REQUIRE( emptyArray.height() == 0 );
	}
}
