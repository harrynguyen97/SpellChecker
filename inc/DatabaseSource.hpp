#ifndef _DATABASE_SOURCE_H_
#define _DATABASE_SOURCE_H_

#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>

class Database
{
public:
	Database(const std::string path_to_file);
	
	//
	// Hash data from %.txt to HashTable
	// key[string]/value[int (which can be any type cus HashTable no need value)]
	// Ex: Bucket 0: key["information"]/value[0]
	//     Bucket 5: key["intergrated"]/value[0]
	// Take no argument
	// Return a HashTable 
	//
	std::unordered_map<std::string, int> hashIntoTable();

	//
	// Print content of all buckets in HashTable 
	// Take a HashTable as argument
	// Return none
	//
	void 
	printBucketContent(const std::unordered_map<std::string, int>& 
					   mapped_dictionary);


	// 
	// Print statistic of HashTable 
	// includes Total words,
	// 			HashTable size,
	//			Total bucket used,
	//          Used percentage,
	//			Load factor
	// Take a HashTable as argument
	// Return none
	//
	void 
	printStatistic(const std::unordered_map<std::string, int>& 
				   mapped_dictionary);
	
	// 
	// Get total number of words in the dictionary
	// Take HashTable as argument
	// return unsigned integer 32 bit
	// 
	const uint32_t 
	getNumberOfWords(const std::unordered_map<std::string, int>& 
					 mapped_dictionary);

protected:
	// Declare HashTable
	std::unordered_map<std::string, int> p_mapped_dictionary;

private:
	// Path to dictionary file
	std::string m_path_to_file;

	// Declare FILE type for dictionary file
	std::ifstream m_dictFile;

	// Each English word
	std::string m_engWord;
};

#endif