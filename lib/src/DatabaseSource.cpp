#include "DatabaseSource.hpp"

//
// Constructor with path to dictionary file
// 
Database::Database(const std::string path_to_file):
	m_path_to_file(path_to_file) {}

// 
// Hash dictionary file into HashTable
//
std::unordered_map<std::string, int>
Database::hashIntoTable()
{
	m_dictFile.open(m_path_to_file);
	if (m_dictFile.is_open()) {
		// Get each line and store it in m_endWord
		while(std::getline(m_dictFile, m_engWord)) 
			// Insert each word into HashTable with key[word]/value[0]
			p_mapped_dictionary.insert(std::pair<std::string, int> 
									   (m_engWord, 0));
		m_dictFile.close();
	}
	else 
		// If having problem while opening file
		// then throw a exception
		throw "Unable to load database file.";

	// Return a HashTable
	return p_mapped_dictionary;
}

//
// Print contents of all bucket in HashTable
//
void 
Database::printBucketContent(const std::unordered_map<std::string, 
							 int>& mapped_dictionary)
{
	// Scan from 0 to number of bucket in the HashTable
	for (uint32_t i = 0; i < mapped_dictionary.bucket_count(); ++i) {
		std::cout << "Bucket #" << i << ": ";

		// "auto" is a short way to represent common and long datatype
		// Scan in each bucket and display all contents from begin() to end()
		for (auto it = mapped_dictionary.begin(i); 
			 it != mapped_dictionary.end(i); 
			 ++it) 

			// Display key[word]
			std::cout << it->first << " ";
		std::cout << std::endl;
	}
}

void
Database::printStatistic(const std::unordered_map<std::string, 
					     int>& mapped_dictionary)
{
	std::cout << "Total English words: " 
			  << mapped_dictionary.size() 
			  << std::endl;

	std::cout << "Hash Table size: " 
			  << mapped_dictionary.bucket_count() / 
			     mapped_dictionary.load_factor()
			  << std::endl;

	std::cout << "Total bucket used: " 
	          << mapped_dictionary.bucket_count() 
	          << std::endl;
	
	std::cout << "Used percentage: " 
			  << mapped_dictionary.load_factor() * 100 << "%"
			  << std::endl;

	std::cout << "Load factor: " 
	          << mapped_dictionary.load_factor() 
	          << std::endl;
}

//
// Get toal words in dictionary file
//
const uint32_t 
Database::getNumberOfWords(const std::unordered_map<std::string, 
						   int>& mapped_dictionary)
{
	return mapped_dictionary.size();
}
