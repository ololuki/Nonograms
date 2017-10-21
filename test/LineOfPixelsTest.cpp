#include "catch.hpp"
#include "../app/field/LineOfPixels.h"
#include "../app/utils/NVector.h"


TEST_CASE("LineOfPixels") {
	unsigned int size = 2;
	AddressOnDrawingArea address(13, 46);
	LineOfPixels lineOfPixels(NVector<Pixel>(size, Pixel(address)));
	
	SECTION("size() should return size") {
		REQUIRE(lineOfPixels.size() == 2);
	}
	
	SECTION( "Pixels implicitly should be empty" ) {
		REQUIRE( lineOfPixels[0].isEmpty() == true );
		REQUIRE( lineOfPixels[1].isEmpty() == true );
	}
	
	SECTION( "operator[] should return reference to Pixel" ) {
		Pixel &pixel = lineOfPixels[0];
		REQUIRE( lineOfPixels[0].isDot() == false );
		pixel.makeDot();
		REQUIRE( lineOfPixels[0].isDot() == true );
	}
	
	SECTION( "getPixelAt should return reference to Pixel" ) {
		Pixel &pixel = lineOfPixels.getPixelAt(0);
		REQUIRE( lineOfPixels[0].isDot() == false );
		pixel.makeDot();
		REQUIRE( lineOfPixels[0].isDot() == true );
	}
	
	SECTION( "max size should be at least 10000" ) {
		unsigned int sizeMax = 10000;
		AddressOnDrawingArea address(sizeMax, sizeMax);
		LineOfPixels lineOfPixels(NVector<Pixel>(sizeMax, Pixel(address)));
		REQUIRE( lineOfPixels.size() == sizeMax );
	}
	
	SECTION( "Address of Pixels should be same as given in constructor" ) {
		REQUIRE( lineOfPixels.getPixelAt(0).getAddress() == address );
		REQUIRE( lineOfPixels[0].getAddress() == address );
		REQUIRE( lineOfPixels.getPixelAt(1).getAddress() == address );
		REQUIRE( lineOfPixels[1].getAddress() == address );
	}
	
	SECTION( "address should stay unchanged after makePixelAt" ) {
		lineOfPixels[0].makeFilledBlack();
		REQUIRE( lineOfPixels[0].getAddress() == address );
		lineOfPixels[0].makeDot();
		REQUIRE( lineOfPixels[0].getAddress() == address );
	}
	
	SECTION( "Pixels are filled black after setting them" ) {
		lineOfPixels[0].makeFilledBlack();
		REQUIRE( lineOfPixels[0].isFilledBlack() == true );
	}
	
	SECTION( "Pixels are dot after setting them" ) {
		lineOfPixels[0].makeDot();
		REQUIRE( lineOfPixels[0].isDot() == true );
	}
}
