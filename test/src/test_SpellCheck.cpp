#include "catch.hpp"
#include "SpellCheck.hpp"
#include "DatabaseSource.hpp"
#include <string>

#include <unordered_map>
#include <vector>
#include <map>

using Catch::Matchers::VectorContains;

Database engDict("../bin/words.txt");
std::unordered_map<std::string, int> engDictTable = engDict.hashIntoTable();

SpellCheck UT_SpellCheck(engDictTable);
SentenceCheck UT_SentenceCheck(engDictTable);

TEST_CASE("Test Word Spelling Checking", "[SpellCheck::suggestion]")
{
	SECTION("Try Alteration, Insertion, Deletion, Transposition Checking") {
		REQUIRE_THAT(UT_SpellCheck.suggest("governmet"), 
					 VectorContains(static_cast<std::string>("government")));
		REQUIRE_THAT(UT_SpellCheck.suggest("internatgonal"), 
			 		 VectorContains(static_cast<std::string>("international")));
		REQUIRE_THAT(UT_SpellCheck.suggest("infomration"), 
					 VectorContains(static_cast<std::string>("information")));
		REQUIRE_THAT(UT_SpellCheck.suggest("educatione"), 
					 VectorContains(static_cast<std::string>("education")));
	}

	SECTION("Try \"No Typo\" Scenario") {
		REQUIRE(UT_SpellCheck.suggest("community").at(0) == "no_typo");
	}

	SECTION("Try \"No Suggestion\" Scenario") {
		REQUIRE(UT_SpellCheck.suggest("shbbfjfssfdlb").at(0) == 
														"No suggestion found.");
	}
}

TEST_CASE("Test Splitting Sentence to Words with Delimiter", 
		  "[SentenceCheck::split(delim)]")
{
	std::string delim = " ";

	SECTION("Try split a valid sentence (with words)") {
		std::string testSentence = " a unit test sentence  ";
		std::vector<std::string> UT_tokenVector = 
			UT_SentenceCheck.split(testSentence, delim);
		
		REQUIRE(UT_tokenVector.at(0) == "a");
		REQUIRE(UT_tokenVector.at(1) == "unit");
		REQUIRE(UT_tokenVector.at(2) == "test");
		REQUIRE(UT_tokenVector.at(3) == "sentence");
	}

	SECTION("Try splitting an empty sentence") {
		std::string testSentence = "";
		std::vector<std::string> UT_tokenVector = 
			UT_SentenceCheck.split(testSentence, delim);
		REQUIRE(UT_tokenVector.empty() == true);
	}
}

TEST_CASE("Test Splitting Sentence to Words with default Delimiter", 
		  "[SentenceCheck::split")
{
	SECTION("Try splitting a valid sentence (with words)") {
		std::string testSentence = " a~!@#$ unit%^&*() test)_+`-= sentence[]\\{ }|:\";' ' ,./ <>?  ";

		std::vector<std::string> UT_tokenVector = 
			UT_SentenceCheck.split(testSentence);
		
		REQUIRE(UT_tokenVector.at(0) == "a");
		REQUIRE(UT_tokenVector.at(1) == "unit");
		REQUIRE(UT_tokenVector.at(2) == "test");
		REQUIRE(UT_tokenVector.at(3) == "sentence");
	}

	SECTION("Try splitting an invalid sentence (all symbols)") {
		std::string testSentence = " ~!@#$%^&*( )_+`-={}|[]\\:  \", ./<>?  ";
		std::vector<std::string> UT_tokenVector = 
			UT_SentenceCheck.split(testSentence);
		REQUIRE(UT_tokenVector.empty() == true);
	}
	SECTION("Try splitting an empty sentence") {
		std::string testSentence = "";
		std::vector<std::string> UT_tokenVector = 
			UT_SentenceCheck.split(testSentence);
		REQUIRE(UT_tokenVector.empty() == true);
	}
}

TEST_CASE("Test Uppercase to Lowercase", "[SentenceCheck::toLower]")
{

	SECTION("Try UPPERCASE SENTENCE with symbols") {
		std::string testSentence = "@A [UNIT] TEsT SeNtENCE";
		std::vector<std::string> UT_testTokens = 
									UT_SentenceCheck.split(testSentence); 
		
		UT_testTokens = UT_SentenceCheck.toLower(UT_testTokens);
		
		REQUIRE(UT_testTokens.at(0) == "a");
		REQUIRE(UT_testTokens.at(1) == "unit");
		REQUIRE(UT_testTokens.at(2) == "test");
		REQUIRE(UT_testTokens.at(3) == "sentence");
	}

	SECTION("Try Invalid Sentence with all symbols") {
		std::string testSentence = "#$%&*( $%^&{||\\:\",./";

		std::vector<std::string> UT_testTokens = 
									UT_SentenceCheck.split(testSentence); 
		
		UT_testTokens = UT_SentenceCheck.toLower(UT_testTokens);

		REQUIRE(UT_testTokens.empty() == true); 
	}

	SECTION("Try Empty Sentence") {
		std::string testSentence = "";

		std::vector<std::string> UT_testTokens = 
									UT_SentenceCheck.split(testSentence); 
		
		UT_testTokens = UT_SentenceCheck.toLower(UT_testTokens);

		REQUIRE(UT_testTokens.empty() == true); 
	}
}

TEST_CASE("Test Spelling Suggestion Map", "[SentenceCheck::getMap")
{
	std::map<std::string, std::vector<std::string>> UT_suggestionMap;
	
	std::vector<std::string> UT_tokens = {"governmet", "internatgonal", 
										  "infomration", "educatione",
										  "community", "jasfvsvdsdk"};

	UT_suggestionMap = UT_SentenceCheck.getMap(UT_tokens);
	SECTION("Try Alteration, Deletion, Insertion, Transposition") {
		REQUIRE_THAT(UT_suggestionMap["governmet"], 
					 VectorContains(static_cast<std::string> ("government"))); 

		REQUIRE_THAT(UT_suggestionMap["internatgonal"], 
					 VectorContains(static_cast<std::string> ("international"))); 

		REQUIRE_THAT(UT_suggestionMap["infomration"], 
					 VectorContains(static_cast<std::string> ("information"))); 

		REQUIRE_THAT(UT_suggestionMap["educatione"], 
					 VectorContains(static_cast<std::string> ("education"))); 
	}

	SECTION("Try No typo") {
		REQUIRE(UT_suggestionMap["community"].at(0) == "no_typo");
	}

	SECTION("Try No suggestion") {
		REQUIRE(UT_suggestionMap["jasfvsvdsdk"].at(0) == "No suggestion found.");
	}
}