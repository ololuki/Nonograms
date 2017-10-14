#include "catch.hpp"
#include "../app/field/AddressOnDrawingArea.h"


TEST_CASE("AddressOnDrawingArea") {
	unsigned int xA = 0;
	unsigned int yA = 1;
	unsigned int xB = xA + 2;
	unsigned int yB = yA + 2;
	AddressOnDrawingArea addressA(xA, yA);
	AddressOnDrawingArea addressADuplicate(xA, yA);
	AddressOnDrawingArea addressB(xB, yB);
	AddressOnDrawingArea addressBDuplicate(xB, yB);
	
	SECTION( "x and y of Address should be same as given in constructor" ) {
		REQUIRE( addressA.getX() == xA );
		REQUIRE( addressA.getY() == yA );
	}
	
	SECTION( "Address compared with itself is equal" ) {
		REQUIRE( addressA == addressA );
	}
	
	SECTION( "Addresses with same x and y are equal" ) {
		REQUIRE( addressA == addressADuplicate );
		REQUIRE( addressB == addressBDuplicate );
	}
	
	SECTION( "Addresses with different x and y are NOT equal" ) {
		REQUIRE( (addressA == addressB) == false );
		unsigned int a = 1;
		REQUIRE( (AddressOnDrawingArea(a, a) == AddressOnDrawingArea(a, a+1)) == false );
		REQUIRE( (AddressOnDrawingArea(a, a) == AddressOnDrawingArea(a+1, a)) == false );
	}
}
