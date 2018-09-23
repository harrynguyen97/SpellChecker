#ifndef _SPELL_CHECK_H_
#define _SPELL_CHECK_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>

//
// SpellCheck is used for spell checking a single word
//
class SpellCheck
{
public:
	// Constructor with a HashTable
	SpellCheck(const std::unordered_map<std::string, int>& mapped_dictionary);
	
	// 
	// Suggest all posible cases of a mistyped word
	// includes alteration, deletion, insertion, transposition
	//
	// Take a \var word as argument
	// return a vector which contains:
	// 		set of suggested words
	//		"no_typo" if there is no mistyped word at all
	//      "No suggestion found." if mistyped but can not give suggestion
	//
	std::vector<std::string> suggest(const std::string word);

private:
	// Iterator for HashTable
	std::unordered_map<std::string, int>::iterator m_it;

	// HashTable 
	std::unordered_map<std::string, int> m_mapped_dictionary;
};


//
// SentenceCheck provides spell checking for whole sentence
// 
class SentenceCheck: public SpellCheck
{
public:
	// Constructor with a HashTable
	SentenceCheck(const std::unordered_map<std::string, int>& mapped_dictionary);

	//
	// Split sentence into words 
	// delimiter(delim) is the character ignored in the sentence
	// Ex: "this is &* string." which delim = "&*. "
	// 		is splited into "this", "is", "string"
	// 
	// Return a vector of string
	std::vector<std::string> split(std::string& str, std::string delim);

	// 
	// Split sentence into words with default delimiter
	// See .cpp file for more info on the default delimiter
	// 
	// return a vector of string
	//
	std::vector<std::string> split(std::string& str);

	//
	// Convert UPPERCASE to lowercase
	// 
	// Take vector of string as argument (can use the splited sentence above)
	// Return vector of string in lowercase
	//
	std::vector<std::string> toLower(std::vector<std::string>& tokens);

	// 
	// Get HashTable of suggestion
	// key[mistyped_word]/value[vector_of_suggestion]
	//
	// Ex:    key                   value
	// 	   efective      vector<ejective elective effective>
	// 
	// Take vector of lowercase tokens above as argument
	// Return HashTable as described above
	//
	std::map<std::string, std::vector<std::string>> 
	getMap(const std::vector<std::string> tokens);
};

#endif