#include "catch.hpp"
#include "../app/field/BlocksDescriptionField.h"
#include "../app/field/AddressOfHint.h"


TEST_CASE("BlocksDescriptionField insertDescriptionBefore") {
	int numberOfLines = 2;
	int lineNumber = 1;
	int blockValueDefault = 0;
	int blockValueAtZero = 5;
	int blockValueAtFirst = 10;
	BlocksDescriptionField blocksDescriptionField(numberOfLines, AddressOfHint::orientation::VERTICAL);
	AddressOfHint addressZero = AddressOfHint(AddressOfHint::VERTICAL, lineNumber, 0);
	AddressOfHint addressFirst = AddressOfHint(AddressOfHint::VERTICAL, lineNumber, 1);
	AddressOfHint addressSecond = AddressOfHint(AddressOfHint::VERTICAL, lineNumber, 2);
	AddressOfHint addressThird = AddressOfHint(AddressOfHint::VERTICAL, lineNumber, 3);
	Hint hintAtZero = Hint(addressZero, blockValueAtZero);
	Hint hintAtFirst = Hint(addressFirst, blockValueAtFirst);
	
	SECTION( "number of lines should increase after insert" ) {
		blocksDescriptionField.insertHintBefore(hintAtZero);
		REQUIRE( blocksDescriptionField.numberOfBlocksInLine(lineNumber) == 2 );
		blocksDescriptionField.insertHintBefore(hintAtZero);
		REQUIRE( blocksDescriptionField.numberOfBlocksInLine(lineNumber) == 3 );
	}
	
	SECTION( "adresses after increase should be same as count in line" ) {
		blocksDescriptionField.insertHintBefore(hintAtZero);
		REQUIRE (blocksDescriptionField.getHint(addressZero).getAddress() == addressZero);
		REQUIRE (blocksDescriptionField.getHint(addressFirst).getAddress() == addressFirst);
		blocksDescriptionField.insertHintBefore(hintAtFirst);
		REQUIRE (blocksDescriptionField.getHint(addressZero).getAddress() == addressZero);
		REQUIRE (blocksDescriptionField.getHint(addressFirst).getAddress() == addressFirst);
		REQUIRE (blocksDescriptionField.getHint(addressSecond).getAddress() == addressSecond);
		blocksDescriptionField.insertHintBefore(hintAtZero);
		REQUIRE (blocksDescriptionField.getHint(addressZero).getAddress() == addressZero);
		REQUIRE (blocksDescriptionField.getHint(addressFirst).getAddress() == addressFirst);
		REQUIRE (blocksDescriptionField.getHint(addressSecond).getAddress() == addressSecond);
		REQUIRE (blocksDescriptionField.getHint(addressThird).getAddress() == addressThird);
	}
	
	SECTION( "value after increase should be shifted properly" ) {
		blocksDescriptionField.insertHintBefore(hintAtZero);
		REQUIRE (blocksDescriptionField.getHint(addressZero).getBlockSize() == blockValueAtZero);
		REQUIRE (blocksDescriptionField.getHint(addressFirst).getBlockSize() == blockValueDefault);
		blocksDescriptionField.insertHintBefore(hintAtFirst);
		REQUIRE (blocksDescriptionField.getHint(addressZero).getBlockSize() == blockValueAtZero);
		REQUIRE (blocksDescriptionField.getHint(addressFirst).getBlockSize() == blockValueAtFirst);
		REQUIRE (blocksDescriptionField.getHint(addressSecond).getBlockSize() == blockValueDefault);
		blocksDescriptionField.insertHintBefore(hintAtFirst);
		REQUIRE (blocksDescriptionField.getHint(addressZero).getBlockSize() == blockValueAtZero);
		REQUIRE (blocksDescriptionField.getHint(addressFirst).getBlockSize() == blockValueAtFirst);
		REQUIRE (blocksDescriptionField.getHint(addressSecond).getBlockSize() == blockValueAtFirst);
		REQUIRE (blocksDescriptionField.getHint(addressThird).getBlockSize() == blockValueDefault);
	}
}


TEST_CASE("BlocksDescriptionField updateDescription") {
	int numberOfLines = 3;
	int firstLine = 1;
	int blockSizeValue = 5;
	BlocksDescriptionField blocksDescriptionField(numberOfLines, AddressOfHint::orientation::VERTICAL);
	AddressOfHint addressCountZeroLineFirst = AddressOfHint(AddressOfHint::VERTICAL, firstLine, 0);
	Hint hintAtCountZeroLineFirst = Hint(addressCountZeroLineFirst, blockSizeValue);
	
	SECTION( "number of lines should not change after update" ) {
		int namberOfBlocksInFirstLine = blocksDescriptionField.numberOfBlocksInLine(firstLine);
		blocksDescriptionField.updateHint(hintAtCountZeroLineFirst);
		REQUIRE( blocksDescriptionField.numberOfBlocksInLine(firstLine) == namberOfBlocksInFirstLine );
	}
	
	SECTION( "address should not change after update" ) {
		blocksDescriptionField.updateHint(hintAtCountZeroLineFirst);
		REQUIRE( blocksDescriptionField.getHint(addressCountZeroLineFirst).getAddress() == addressCountZeroLineFirst );
	}
	
	SECTION( "block size value should change after update" ) {
		blocksDescriptionField.updateHint(hintAtCountZeroLineFirst);
		REQUIRE( blocksDescriptionField.getHint(addressCountZeroLineFirst).getBlockSize() == blockSizeValue );
	}
}


TEST_CASE("BlocksDescriptionField deleteDescription") {
	int numberOfLines = 2;
	int lineNumber = 1;
	int blockValueDefault = 0;
	int blockValueAtZero = 5;
	int blockValueAtFirst = 10;
	BlocksDescriptionField blocksDescriptionField(numberOfLines, AddressOfHint::orientation::VERTICAL);
	AddressOfHint addressZero = AddressOfHint(AddressOfHint::VERTICAL, lineNumber, 0);
	AddressOfHint addressFirst = AddressOfHint(AddressOfHint::VERTICAL, lineNumber, 1);
	AddressOfHint addressSecond = AddressOfHint(AddressOfHint::VERTICAL, lineNumber, 2);
	AddressOfHint addressThird = AddressOfHint(AddressOfHint::VERTICAL, lineNumber, 3);
	Hint hintAtZero = Hint(addressZero, blockValueAtZero);
	Hint hintAtFirst = Hint(addressFirst, blockValueAtFirst);
	blocksDescriptionField.insertHintBefore(hintAtZero);
	blocksDescriptionField.insertHintBefore(hintAtFirst);
	blocksDescriptionField.insertHintBefore(hintAtFirst);
	
	SECTION( "number of hints in line should decrease after delete" ) {
		REQUIRE( blocksDescriptionField.numberOfBlocksInLine(lineNumber) == 4 );
		blocksDescriptionField.deleteHint(hintAtFirst);
		REQUIRE( blocksDescriptionField.numberOfBlocksInLine(lineNumber) == 3 );
		blocksDescriptionField.deleteHint(hintAtZero);
		REQUIRE( blocksDescriptionField.numberOfBlocksInLine(lineNumber) == 2 );
	}
	
	SECTION( "adresses after delete should be same as count in line" ) {
		REQUIRE (blocksDescriptionField.getHint(addressZero).getAddress() == addressZero);
		REQUIRE (blocksDescriptionField.getHint(addressFirst).getAddress() == addressFirst);
		REQUIRE (blocksDescriptionField.getHint(addressSecond).getAddress() == addressSecond);
		REQUIRE (blocksDescriptionField.getHint(addressThird).getAddress() == addressThird);
		blocksDescriptionField.deleteHint(hintAtZero);
		REQUIRE (blocksDescriptionField.getHint(addressZero).getAddress() == addressZero);
		REQUIRE (blocksDescriptionField.getHint(addressFirst).getAddress() == addressFirst);
		REQUIRE (blocksDescriptionField.getHint(addressSecond).getAddress() == addressSecond);
		blocksDescriptionField.deleteHint(hintAtZero);
		REQUIRE (blocksDescriptionField.getHint(addressZero).getAddress() == addressZero);
		REQUIRE (blocksDescriptionField.getHint(addressFirst).getAddress() == addressFirst);
	}
	
	SECTION( "hint can NOT be deleted if there is only ONE left") {
		BlocksDescriptionField containOneDescription(numberOfLines, AddressOfHint::orientation::VERTICAL);
		REQUIRE( containOneDescription.numberOfBlocksInLine(lineNumber) == 1 );
		containOneDescription.deleteHint(hintAtZero);
		REQUIRE( containOneDescription.numberOfBlocksInLine(lineNumber) == 1 );
	}
	
	SECTION( "values after delete should be shifted properly" ) {
		REQUIRE (blocksDescriptionField.getHint(addressZero).getBlockSize() == blockValueAtZero);
		REQUIRE (blocksDescriptionField.getHint(addressFirst).getBlockSize() == blockValueAtFirst);
		REQUIRE (blocksDescriptionField.getHint(addressSecond).getBlockSize() == blockValueAtFirst);
		REQUIRE (blocksDescriptionField.getHint(addressThird).getBlockSize() == blockValueDefault);
		blocksDescriptionField.deleteHint(hintAtZero);
		REQUIRE (blocksDescriptionField.getHint(addressZero).getBlockSize() == blockValueAtFirst);
		REQUIRE (blocksDescriptionField.getHint(addressFirst).getBlockSize() == blockValueAtFirst);
		REQUIRE (blocksDescriptionField.getHint(addressSecond).getBlockSize() == blockValueDefault);
		blocksDescriptionField.deleteHint(hintAtZero);
		REQUIRE (blocksDescriptionField.getHint(addressZero).getBlockSize() == blockValueAtFirst);
		REQUIRE (blocksDescriptionField.getHint(addressFirst).getBlockSize() == blockValueDefault);
		blocksDescriptionField.deleteHint(hintAtFirst);
		REQUIRE (blocksDescriptionField.getHint(addressZero).getBlockSize() == blockValueAtFirst);
	}
}
