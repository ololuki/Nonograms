#include "catch.hpp"
#include "../app/field/BlocksDescriptionField.h"
#include "../app/field/AddressOnBlocksDescription.h"


TEST_CASE("BlocksDescriptionField insertDecriptionBefore") {
	size_t numberOfLines = 2;
	size_t lineNumber = 1;
	size_t blockValueDefault = 0;
	size_t blockValueAtZero = 5;
	size_t blockValueAtFirst = 10;
	BlocksDescriptionField blocksDescriptionField(numberOfLines, AddressOnBlocksDescription::orientation::VERTICAL);
	AddressOnBlocksDescription addressZero = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, lineNumber, 0);
	AddressOnBlocksDescription addressFirst = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, lineNumber, 1);
	AddressOnBlocksDescription addressSecond = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, lineNumber, 2);
	AddressOnBlocksDescription addressThird = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, lineNumber, 3);
	BlockDescription descriptionAtZero = BlockDescription(addressZero, blockValueAtZero);
	BlockDescription descriptionAtFirst = BlockDescription(addressFirst, blockValueAtFirst);
	
	SECTION( "number of lines should increase after insert" ) {
		blocksDescriptionField.insertDescriptionBefore(descriptionAtZero);
		REQUIRE( blocksDescriptionField.numberOfBlocksInLine(lineNumber) == 2 );
		blocksDescriptionField.insertDescriptionBefore(descriptionAtZero);
		REQUIRE( blocksDescriptionField.numberOfBlocksInLine(lineNumber) == 3 );
	}
	
	SECTION( "adresses after increase should be same as count in line" ) {
		blocksDescriptionField.insertDescriptionBefore(descriptionAtZero);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressZero).getAddress() == addressZero);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressFirst).getAddress() == addressFirst);
		blocksDescriptionField.insertDescriptionBefore(descriptionAtFirst);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressZero).getAddress() == addressZero);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressFirst).getAddress() == addressFirst);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressSecond).getAddress() == addressSecond);
		blocksDescriptionField.insertDescriptionBefore(descriptionAtZero);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressZero).getAddress() == addressZero);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressFirst).getAddress() == addressFirst);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressSecond).getAddress() == addressSecond);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressThird).getAddress() == addressThird);
	}
	
	SECTION( "value after increase should be shifted properly" ) {
		blocksDescriptionField.insertDescriptionBefore(descriptionAtZero);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressZero).getBlockSize() == blockValueAtZero);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressFirst).getBlockSize() == blockValueDefault);
		blocksDescriptionField.insertDescriptionBefore(descriptionAtFirst);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressZero).getBlockSize() == blockValueAtZero);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressFirst).getBlockSize() == blockValueAtFirst);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressSecond).getBlockSize() == blockValueDefault);
		blocksDescriptionField.insertDescriptionBefore(descriptionAtFirst);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressZero).getBlockSize() == blockValueAtZero);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressFirst).getBlockSize() == blockValueAtFirst);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressSecond).getBlockSize() == blockValueAtFirst);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressThird).getBlockSize() == blockValueDefault);
	}
}


TEST_CASE("BlocksDescriptionField deleteDecription") {
	size_t numberOfLines = 2;
	size_t lineNumber = 1;
	size_t blockValueDefault = 0;
	size_t blockValueAtZero = 5;
	size_t blockValueAtFirst = 10;
	BlocksDescriptionField blocksDescriptionField(numberOfLines, AddressOnBlocksDescription::orientation::VERTICAL);
	AddressOnBlocksDescription addressZero = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, lineNumber, 0);
	AddressOnBlocksDescription addressFirst = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, lineNumber, 1);
	AddressOnBlocksDescription addressSecond = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, lineNumber, 2);
	AddressOnBlocksDescription addressThird = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, lineNumber, 3);
	BlockDescription descriptionAtZero = BlockDescription(addressZero, blockValueAtZero);
	BlockDescription descriptionAtFirst = BlockDescription(addressFirst, blockValueAtFirst);
	blocksDescriptionField.insertDescriptionBefore(descriptionAtZero);
	blocksDescriptionField.insertDescriptionBefore(descriptionAtFirst);
	blocksDescriptionField.insertDescriptionBefore(descriptionAtFirst);
	
	SECTION( "number of lines should decrease after delete" ) {
		REQUIRE( blocksDescriptionField.numberOfBlocksInLine(lineNumber) == 4 );
		blocksDescriptionField.deleteDescription(descriptionAtFirst);
		REQUIRE( blocksDescriptionField.numberOfBlocksInLine(lineNumber) == 3 );
		blocksDescriptionField.deleteDescription(descriptionAtZero);
		REQUIRE( blocksDescriptionField.numberOfBlocksInLine(lineNumber) == 2 );
	}
	
	SECTION( "adresses after delete should be same as count in line" ) {
		REQUIRE (blocksDescriptionField.getBlockDescription(addressZero).getAddress() == addressZero);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressFirst).getAddress() == addressFirst);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressSecond).getAddress() == addressSecond);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressThird).getAddress() == addressThird);
		blocksDescriptionField.deleteDescription(descriptionAtZero);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressZero).getAddress() == addressZero);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressFirst).getAddress() == addressFirst);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressSecond).getAddress() == addressSecond);
		blocksDescriptionField.deleteDescription(descriptionAtZero);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressZero).getAddress() == addressZero);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressFirst).getAddress() == addressFirst);
	}
	
	SECTION( "blockDescription can NOT be deleted if there is only ONE left") {
		BlocksDescriptionField containOneDescription(numberOfLines, AddressOnBlocksDescription::orientation::VERTICAL);
		REQUIRE( containOneDescription.numberOfBlocksInLine(lineNumber) == 1 );
		containOneDescription.deleteDescription(descriptionAtZero);
		REQUIRE( containOneDescription.numberOfBlocksInLine(lineNumber) == 1 );
	}
	
	SECTION( "values after delete should be shifted properly" ) {
		REQUIRE (blocksDescriptionField.getBlockDescription(addressZero).getBlockSize() == blockValueAtZero);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressFirst).getBlockSize() == blockValueAtFirst);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressSecond).getBlockSize() == blockValueAtFirst);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressThird).getBlockSize() == blockValueDefault);
		blocksDescriptionField.deleteDescription(descriptionAtZero);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressZero).getBlockSize() == blockValueAtFirst);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressFirst).getBlockSize() == blockValueAtFirst);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressSecond).getBlockSize() == blockValueDefault);
		blocksDescriptionField.deleteDescription(descriptionAtZero);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressZero).getBlockSize() == blockValueAtFirst);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressFirst).getBlockSize() == blockValueDefault);
		blocksDescriptionField.deleteDescription(descriptionAtFirst);
		REQUIRE (blocksDescriptionField.getBlockDescription(addressZero).getBlockSize() == blockValueAtFirst);
	}
}
