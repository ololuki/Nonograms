#include "catch.hpp"
#include "../app/field/LineOfCells.h"
#include "../app/utils/NVector.h"


TEST_CASE("LineOfCells") {
	unsigned int size = 2;
	AddressOfCell address(13, 46);
	LineOfCells lineOfCells(NVector<Cell>(size, Cell(address)));
	
	SECTION("size() should return size") {
		REQUIRE(lineOfCells.size() == 2);
	}
	
	SECTION( "Cells implicitly should be empty" ) {
		REQUIRE( lineOfCells[0].isEmpty() == true );
		REQUIRE( lineOfCells[1].isEmpty() == true );
	}
	
	SECTION( "operator[] should return reference to Cell" ) {
		Cell &cell = lineOfCells[0];
		REQUIRE( lineOfCells[0].isDot() == false );
		cell.makeDot();
		REQUIRE( lineOfCells[0].isDot() == true );
	}
	
	SECTION( "getCellAt should return reference to Cell" ) {
		Cell &cell = lineOfCells.getCellAt(0);
		REQUIRE( lineOfCells[0].isDot() == false );
		cell.makeDot();
		REQUIRE( lineOfCells[0].isDot() == true );
	}
	
	SECTION( "max size should be at least 10000" ) {
		unsigned int sizeMax = 10000;
		AddressOfCell address(sizeMax, sizeMax);
		LineOfCells lineOfCells(NVector<Cell>(sizeMax, Cell(address)));
		REQUIRE( lineOfCells.size() == sizeMax );
	}
	
	SECTION( "Address of Cells should be same as given in constructor" ) {
		REQUIRE( lineOfCells.getCellAt(0).getAddress() == address );
		REQUIRE( lineOfCells[0].getAddress() == address );
		REQUIRE( lineOfCells.getCellAt(1).getAddress() == address );
		REQUIRE( lineOfCells[1].getAddress() == address );
	}
	
	SECTION( "address should stay unchanged after makeFilled and makeDot" ) {
		lineOfCells[0].makeFilledBlack();
		REQUIRE( lineOfCells[0].getAddress() == address );
		lineOfCells[0].makeDot();
		REQUIRE( lineOfCells[0].getAddress() == address );
	}
	
	SECTION( "Cells are filled black after setting them" ) {
		lineOfCells[0].makeFilledBlack();
		REQUIRE( lineOfCells[0].isFilledBlack() == true );
	}
	
	SECTION( "Cells are dot after setting them" ) {
		lineOfCells[0].makeDot();
		REQUIRE( lineOfCells[0].isDot() == true );
	}
}
