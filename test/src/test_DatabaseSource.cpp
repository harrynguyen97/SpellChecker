#include "DatabaseSource.hpp"
#include "catch.hpp"

Database TestDatabase("../bin/words.txt");

TEST_CASE("Test hashing .txt into HashTable", "[hashIntoTable]")
{
	REQUIRE_NOTHROW(TestDatabase.hashIntoTable());
}

TEST_CASE("Test printing bucket content", "[printBucketContent]")
{
	REQUIRE(TestDatabase.hashIntoTable().find("love")->second == 0);
	REQUIRE(TestDatabase.hashIntoTable().find("information")->second == 0);
	REQUIRE(TestDatabase.hashIntoTable().find("interpeduncular")->second == 0);
}

