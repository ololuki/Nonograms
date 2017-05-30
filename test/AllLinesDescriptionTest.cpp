#include "catch.hpp"
#include "../app/field/AllLinesDescription.h"
#include "../app/field/AddressOnBlocksDescription.h"


TEST_CASE("AllLinesDescription insertDecriptionBefore") {
	size_t numberOfLines = 2;
	size_t lineNumber = 1;
	size_t blockValueDefault = 0;
	size_t blockValueAtZero = 5;
	size_t blockValueAtFirst = 10;
	AllLinesDescription allLinesDescription(AddressOnBlocksDescription::orientation::VERTICAL, numberOfLines);
	AddressOnBlocksDescription addressZero = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, lineNumber, 0);
	AddressOnBlocksDescription addressFirst = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, lineNumber, 1);
	AddressOnBlocksDescription addressSecond = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, lineNumber, 2);
	AddressOnBlocksDescription addressThird = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, lineNumber, 3);
	BlockDescription descriptionAtZero = BlockDescription(addressZero, blockValueAtZero);
	BlockDescription descriptionAtFirst = BlockDescription(addressFirst, blockValueAtFirst);
	
	SECTION( "number of lines should increase after insert" ) {
		allLinesDescription.insertDescriptionBefore(descriptionAtZero);
		REQUIRE( allLinesDescription.numberOfBlocksInLine(lineNumber) == 2 );
		allLinesDescription.insertDescriptionBefore(descriptionAtZero);
		REQUIRE( allLinesDescription.numberOfBlocksInLine(lineNumber) == 3 );
	}
	
	SECTION( "adresses after incease should be same as count in line" ) {
		allLinesDescription.insertDescriptionBefore(descriptionAtZero);
		REQUIRE (allLinesDescription.operator()(lineNumber, 0).getAddress() == addressZero);
		REQUIRE (allLinesDescription.operator()(lineNumber, 1).getAddress() == addressFirst);
		allLinesDescription.insertDescriptionBefore(descriptionAtFirst);
		REQUIRE (allLinesDescription.operator()(lineNumber, 0).getAddress() == addressZero);
		REQUIRE (allLinesDescription.operator()(lineNumber, 1).getAddress() == addressFirst);
		REQUIRE (allLinesDescription.operator()(lineNumber, 2).getAddress() == addressSecond);
		allLinesDescription.insertDescriptionBefore(descriptionAtZero);
		REQUIRE (allLinesDescription.operator()(lineNumber, 0).getAddress() == addressZero);
		REQUIRE (allLinesDescription.operator()(lineNumber, 1).getAddress() == addressFirst);
		REQUIRE (allLinesDescription.operator()(lineNumber, 2).getAddress() == addressSecond);
		REQUIRE (allLinesDescription.operator()(lineNumber, 3).getAddress() == addressThird);
	}
	
	SECTION( "value after incease should be shifted properly" ) {
		allLinesDescription.insertDescriptionBefore(descriptionAtZero);
		REQUIRE (allLinesDescription.operator()(lineNumber, 0).getBlockSize() == blockValueAtZero);
		REQUIRE (allLinesDescription.operator()(lineNumber, 1).getBlockSize() == blockValueDefault);
		allLinesDescription.insertDescriptionBefore(descriptionAtFirst);
		REQUIRE (allLinesDescription.operator()(lineNumber, 0).getBlockSize() == blockValueAtZero);
		REQUIRE (allLinesDescription.operator()(lineNumber, 1).getBlockSize() == blockValueAtFirst);
		REQUIRE (allLinesDescription.operator()(lineNumber, 2).getBlockSize() == blockValueDefault);
		allLinesDescription.insertDescriptionBefore(descriptionAtFirst);
		REQUIRE (allLinesDescription.operator()(lineNumber, 0).getBlockSize() == blockValueAtZero);
		REQUIRE (allLinesDescription.operator()(lineNumber, 1).getBlockSize() == blockValueAtFirst);
		REQUIRE (allLinesDescription.operator()(lineNumber, 2).getBlockSize() == blockValueAtFirst);
		REQUIRE (allLinesDescription.operator()(lineNumber, 3).getBlockSize() == blockValueDefault);
	}
}


TEST_CASE("AllLinesDescription deleteDecription") {
	size_t numberOfLines = 2;
	size_t lineNumber = 1;
	size_t blockValueDefault = 0;
	size_t blockValueAtZero = 5;
	size_t blockValueAtFirst = 10;	
	AllLinesDescription allLinesDescription(AddressOnBlocksDescription::orientation::VERTICAL, numberOfLines);
	AddressOnBlocksDescription addressZero = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, lineNumber, 0);
	AddressOnBlocksDescription addressFirst = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, lineNumber, 1);
	AddressOnBlocksDescription addressSecond = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, lineNumber, 2);
	AddressOnBlocksDescription addressThird = AddressOnBlocksDescription(AddressOnBlocksDescription::VERTICAL, lineNumber, 3);
	BlockDescription descriptionAtZero = BlockDescription(addressZero, blockValueAtZero);
	BlockDescription descriptionAtFirst = BlockDescription(addressFirst, blockValueAtFirst);
	allLinesDescription.insertDescriptionBefore(descriptionAtZero);
	allLinesDescription.insertDescriptionBefore(descriptionAtFirst);
	allLinesDescription.insertDescriptionBefore(descriptionAtFirst);
	
	
	SECTION( "number of lines should decrease after delete" ) {
		REQUIRE( allLinesDescription.numberOfBlocksInLine(lineNumber) == 4 );
		allLinesDescription.deleteDescription(descriptionAtFirst);
		REQUIRE( allLinesDescription.numberOfBlocksInLine(lineNumber) == 3 );
		allLinesDescription.deleteDescription(descriptionAtZero);
		REQUIRE( allLinesDescription.numberOfBlocksInLine(lineNumber) == 2 );
	}
	
	SECTION( "adresses after delete should be same as count in line" ) {
		REQUIRE (allLinesDescription.operator()(lineNumber, 0).getAddress() == addressZero);
		REQUIRE (allLinesDescription.operator()(lineNumber, 1).getAddress() == addressFirst);
		REQUIRE (allLinesDescription.operator()(lineNumber, 2).getAddress() == addressSecond);
		REQUIRE (allLinesDescription.operator()(lineNumber, 3).getAddress() == addressThird);
		allLinesDescription.deleteDescription(descriptionAtZero);
		REQUIRE (allLinesDescription.operator()(lineNumber, 0).getAddress() == addressZero);
		REQUIRE (allLinesDescription.operator()(lineNumber, 1).getAddress() == addressFirst);
		REQUIRE (allLinesDescription.operator()(lineNumber, 2).getAddress() == addressSecond);
		allLinesDescription.deleteDescription(descriptionAtZero);
		REQUIRE (allLinesDescription.operator()(lineNumber, 0).getAddress() == addressZero);
		REQUIRE (allLinesDescription.operator()(lineNumber, 1).getAddress() == addressFirst);
	}
	
	SECTION( "blockDescription can NOT be deleted if there is only ONE left") {
		AllLinesDescription containOneDescription(AddressOnBlocksDescription::orientation::VERTICAL, numberOfLines);
		REQUIRE( containOneDescription.numberOfBlocksInLine(lineNumber) == 1 );
		containOneDescription.deleteDescription(descriptionAtZero);
		REQUIRE( containOneDescription.numberOfBlocksInLine(lineNumber) == 1 );
	}
	
	SECTION( "values after delete should be shifted properly" ) {
		REQUIRE (allLinesDescription.operator()(lineNumber, 0).getBlockSize() == blockValueAtZero);
		REQUIRE (allLinesDescription.operator()(lineNumber, 1).getBlockSize() == blockValueAtFirst);
		REQUIRE (allLinesDescription.operator()(lineNumber, 2).getBlockSize() == blockValueAtFirst);
		REQUIRE (allLinesDescription.operator()(lineNumber, 3).getBlockSize() == blockValueDefault);
		allLinesDescription.deleteDescription(descriptionAtZero);
		REQUIRE (allLinesDescription.operator()(lineNumber, 0).getBlockSize() == blockValueAtFirst);
		REQUIRE (allLinesDescription.operator()(lineNumber, 1).getBlockSize() == blockValueAtFirst);
		REQUIRE (allLinesDescription.operator()(lineNumber, 2).getBlockSize() == blockValueDefault);
		allLinesDescription.deleteDescription(descriptionAtZero);
		REQUIRE (allLinesDescription.operator()(lineNumber, 0).getBlockSize() == blockValueAtFirst);
		REQUIRE (allLinesDescription.operator()(lineNumber, 1).getBlockSize() == blockValueDefault);
		allLinesDescription.deleteDescription(descriptionAtFirst);
		REQUIRE (allLinesDescription.operator()(lineNumber, 0).getBlockSize() == blockValueAtFirst);
	}
}
