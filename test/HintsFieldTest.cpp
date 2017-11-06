#include "catch.hpp"
#include "../app/field/HintsField.h"
#include "../app/field/AddressOfHint.h"


TEST_CASE("HintsField insertHintBefore") {
	int numberOfLines = 2;
	int lineNumber = 1;
	int blockValueDefault = 0;
	int blockValueAtZero = 5;
	int blockValueAtFirst = 10;
	HintsField hintsField(numberOfLines, AddressOfHint::orientation::VERTICAL);
	AddressOfHint addressZero = AddressOfHint(AddressOfHint::VERTICAL, lineNumber, 0);
	AddressOfHint addressFirst = AddressOfHint(AddressOfHint::VERTICAL, lineNumber, 1);
	AddressOfHint addressSecond = AddressOfHint(AddressOfHint::VERTICAL, lineNumber, 2);
	AddressOfHint addressThird = AddressOfHint(AddressOfHint::VERTICAL, lineNumber, 3);
	Hint hintAtZero = Hint(addressZero, blockValueAtZero);
	Hint hintAtFirst = Hint(addressFirst, blockValueAtFirst);
	
	SECTION( "number of lines should increase after insert" ) {
		hintsField.insertHintBefore(hintAtZero);
		REQUIRE( hintsField.numberOfBlocksInLine(lineNumber) == 2 );
		hintsField.insertHintBefore(hintAtZero);
		REQUIRE( hintsField.numberOfBlocksInLine(lineNumber) == 3 );
	}
	
	SECTION( "adresses after increase should be same as count in line" ) {
		hintsField.insertHintBefore(hintAtZero);
		REQUIRE (hintsField.getHint(addressZero).getAddress() == addressZero);
		REQUIRE (hintsField.getHint(addressFirst).getAddress() == addressFirst);
		hintsField.insertHintBefore(hintAtFirst);
		REQUIRE (hintsField.getHint(addressZero).getAddress() == addressZero);
		REQUIRE (hintsField.getHint(addressFirst).getAddress() == addressFirst);
		REQUIRE (hintsField.getHint(addressSecond).getAddress() == addressSecond);
		hintsField.insertHintBefore(hintAtZero);
		REQUIRE (hintsField.getHint(addressZero).getAddress() == addressZero);
		REQUIRE (hintsField.getHint(addressFirst).getAddress() == addressFirst);
		REQUIRE (hintsField.getHint(addressSecond).getAddress() == addressSecond);
		REQUIRE (hintsField.getHint(addressThird).getAddress() == addressThird);
	}
	
	SECTION( "value after increase should be shifted properly" ) {
		hintsField.insertHintBefore(hintAtZero);
		REQUIRE (hintsField.getHint(addressZero).getBlockSize() == blockValueAtZero);
		REQUIRE (hintsField.getHint(addressFirst).getBlockSize() == blockValueDefault);
		hintsField.insertHintBefore(hintAtFirst);
		REQUIRE (hintsField.getHint(addressZero).getBlockSize() == blockValueAtZero);
		REQUIRE (hintsField.getHint(addressFirst).getBlockSize() == blockValueAtFirst);
		REQUIRE (hintsField.getHint(addressSecond).getBlockSize() == blockValueDefault);
		hintsField.insertHintBefore(hintAtFirst);
		REQUIRE (hintsField.getHint(addressZero).getBlockSize() == blockValueAtZero);
		REQUIRE (hintsField.getHint(addressFirst).getBlockSize() == blockValueAtFirst);
		REQUIRE (hintsField.getHint(addressSecond).getBlockSize() == blockValueAtFirst);
		REQUIRE (hintsField.getHint(addressThird).getBlockSize() == blockValueDefault);
	}
}


TEST_CASE("HintsField updateHint") {
	int numberOfLines = 3;
	int firstLine = 1;
	int blockSizeValue = 5;
	HintsField hintsField(numberOfLines, AddressOfHint::orientation::VERTICAL);
	AddressOfHint addressCountZeroLineFirst = AddressOfHint(AddressOfHint::VERTICAL, firstLine, 0);
	Hint hintAtCountZeroLineFirst = Hint(addressCountZeroLineFirst, blockSizeValue);
	
	SECTION( "number of lines should not change after update" ) {
		int namberOfBlocksInFirstLine = hintsField.numberOfBlocksInLine(firstLine);
		hintsField.updateHint(hintAtCountZeroLineFirst);
		REQUIRE( hintsField.numberOfBlocksInLine(firstLine) == namberOfBlocksInFirstLine );
	}
	
	SECTION( "address should not change after update" ) {
		hintsField.updateHint(hintAtCountZeroLineFirst);
		REQUIRE( hintsField.getHint(addressCountZeroLineFirst).getAddress() == addressCountZeroLineFirst );
	}
	
	SECTION( "block size value should change after update" ) {
		hintsField.updateHint(hintAtCountZeroLineFirst);
		REQUIRE( hintsField.getHint(addressCountZeroLineFirst).getBlockSize() == blockSizeValue );
	}
}


TEST_CASE("HintsField deleteHint") {
	int numberOfLines = 2;
	int lineNumber = 1;
	int blockValueDefault = 0;
	int blockValueAtZero = 5;
	int blockValueAtFirst = 10;
	HintsField hintsField(numberOfLines, AddressOfHint::orientation::VERTICAL);
	AddressOfHint addressZero = AddressOfHint(AddressOfHint::VERTICAL, lineNumber, 0);
	AddressOfHint addressFirst = AddressOfHint(AddressOfHint::VERTICAL, lineNumber, 1);
	AddressOfHint addressSecond = AddressOfHint(AddressOfHint::VERTICAL, lineNumber, 2);
	AddressOfHint addressThird = AddressOfHint(AddressOfHint::VERTICAL, lineNumber, 3);
	Hint hintAtZero = Hint(addressZero, blockValueAtZero);
	Hint hintAtFirst = Hint(addressFirst, blockValueAtFirst);
	hintsField.insertHintBefore(hintAtZero);
	hintsField.insertHintBefore(hintAtFirst);
	hintsField.insertHintBefore(hintAtFirst);
	
	SECTION( "number of hints in line should decrease after delete" ) {
		REQUIRE( hintsField.numberOfBlocksInLine(lineNumber) == 4 );
		hintsField.deleteHint(hintAtFirst);
		REQUIRE( hintsField.numberOfBlocksInLine(lineNumber) == 3 );
		hintsField.deleteHint(hintAtZero);
		REQUIRE( hintsField.numberOfBlocksInLine(lineNumber) == 2 );
	}
	
	SECTION( "adresses after delete should be same as count in line" ) {
		REQUIRE (hintsField.getHint(addressZero).getAddress() == addressZero);
		REQUIRE (hintsField.getHint(addressFirst).getAddress() == addressFirst);
		REQUIRE (hintsField.getHint(addressSecond).getAddress() == addressSecond);
		REQUIRE (hintsField.getHint(addressThird).getAddress() == addressThird);
		hintsField.deleteHint(hintAtZero);
		REQUIRE (hintsField.getHint(addressZero).getAddress() == addressZero);
		REQUIRE (hintsField.getHint(addressFirst).getAddress() == addressFirst);
		REQUIRE (hintsField.getHint(addressSecond).getAddress() == addressSecond);
		hintsField.deleteHint(hintAtZero);
		REQUIRE (hintsField.getHint(addressZero).getAddress() == addressZero);
		REQUIRE (hintsField.getHint(addressFirst).getAddress() == addressFirst);
	}
	
	SECTION( "hint can NOT be deleted if there is only ONE left") {
		HintsField containOneHint(numberOfLines, AddressOfHint::orientation::VERTICAL);
		REQUIRE( containOneHint.numberOfBlocksInLine(lineNumber) == 1 );
		containOneHint.deleteHint(hintAtZero);
		REQUIRE( containOneHint.numberOfBlocksInLine(lineNumber) == 1 );
	}
	
	SECTION( "values after delete should be shifted properly" ) {
		REQUIRE (hintsField.getHint(addressZero).getBlockSize() == blockValueAtZero);
		REQUIRE (hintsField.getHint(addressFirst).getBlockSize() == blockValueAtFirst);
		REQUIRE (hintsField.getHint(addressSecond).getBlockSize() == blockValueAtFirst);
		REQUIRE (hintsField.getHint(addressThird).getBlockSize() == blockValueDefault);
		hintsField.deleteHint(hintAtZero);
		REQUIRE (hintsField.getHint(addressZero).getBlockSize() == blockValueAtFirst);
		REQUIRE (hintsField.getHint(addressFirst).getBlockSize() == blockValueAtFirst);
		REQUIRE (hintsField.getHint(addressSecond).getBlockSize() == blockValueDefault);
		hintsField.deleteHint(hintAtZero);
		REQUIRE (hintsField.getHint(addressZero).getBlockSize() == blockValueAtFirst);
		REQUIRE (hintsField.getHint(addressFirst).getBlockSize() == blockValueDefault);
		hintsField.deleteHint(hintAtFirst);
		REQUIRE (hintsField.getHint(addressZero).getBlockSize() == blockValueAtFirst);
	}
}
