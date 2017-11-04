#include "catch.hpp"
#include "../app/field/AddressOfCell.h"


TEST_CASE("AddressOfCell") {
	unsigned int xA = 0;
	unsigned int yA = 1;
	unsigned int xB = xA + 2;
	unsigned int yB = yA + 2;
	AddressOfCell addressA(xA, yA);
	AddressOfCell addressADuplicate(xA, yA);
	AddressOfCell addressB(xB, yB);
	AddressOfCell addressBDuplicate(xB, yB);
	
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
		REQUIRE( (AddressOfCell(a, a) == AddressOfCell(a, a+1)) == false );
		REQUIRE( (AddressOfCell(a, a) == AddressOfCell(a+1, a)) == false );
	}
}
