#include "SpellCheck.hpp"

//
// Constructor with a HashTable
//
SpellCheck::SpellCheck(const std::unordered_map<std::string, int>& 
					   mapped_dictionary):
	m_mapped_dictionary(mapped_dictionary) {}

// 
// Suggest all posible cases for a mistyped words
// 
std::vector<std::string> 
SpellCheck::suggest(const std::string word)
{
	std::vector<std::string> suggestion;

	// Find a word in HashTable
	m_it = m_mapped_dictionary.find(word);

	// If do not match any word
	if (m_it == m_mapped_dictionary.end()) {

		//
		// Alteration: a character in word is altered
		// Ex: informtion -> informagion
		//

		// Scan from position 0 to last position of word
		for (uint16_t x = 0; x < word.size(); ++x) {

			// Make a buffer of word
			std::string alteration = word;

			for (char c = 'a'; c <= 'z'; ++c) {
				// Alter position x of word by \var c (from a to z)
				alteration[x] = c;

				// Find if matching any word in dictionary
				m_it = m_mapped_dictionary.find(alteration);
				
				// If match any
				// because if do not match, iterator will be returned to the 
				// end of the map
				if (m_it != m_mapped_dictionary.end())
					// Then push that word (suggestion) in to vector suggestion   
					suggestion.push_back(m_it->first);

				// Erase that word from the dictionary to
				// avoid repeating suggestions multiple times
				// Because suggestions of alteration checking can also be 
				// the suggestions of, say, deletion or insertion checking 
				m_mapped_dictionary.erase(alteration);

				// If do not have this line of code, the result can be weird
				// Example: (1) information -> anformation
				//          (2)             -> aaformation
				//          (3)             -> aaaormation
				//
				// Have to reset \var alteration to initial 
				// \var word everytime doing alterating             
				alteration = word;
			}
		}

		// 
		// Insertion: insert a character to initial word
		// Ex: information -> informatione
		//

		// Because of insertion 1 word, we have to scan from 0 to size() + 1 
		for (uint16_t x = 0; x < word.size() + 1; ++x) {

			// Make a buffer of word
			std::string insertion = word;
			for (char c = 'a'; c <= 'z'; ++c) {
				// Insert 1 \var c character to position x of word
				insertion.insert(x, 1, c);

				// Find if matching any word in dictionary
				m_it = m_mapped_dictionary.find(insertion);
				
				// If matching any
				if (m_it != m_mapped_dictionary.end()) 
					// Then push it (suggested word) to vector suggestion
					suggestion.push_back(m_it->first);

				// Erase word from dictionary to avoid suggestion multiple times
				// See Alteration for more info
				m_mapped_dictionary.erase(insertion);

				// See Alteration for more info
				insertion = word;
			}
		}

		// 
		// Deletion: Delete 1 character from initial word
		// Ex: information -> nformation
		// 

		// Scan through word
		for (uint16_t x = 0; x < word.size(); ++x) {
			// Make buffer of word
			std::string deletion = word;

			// Delete 1 char from position x
			deletion.erase(x, 1);

			// Find if matching any words in dictionary
			m_it = m_mapped_dictionary.find(deletion);

			// If matching any
			if (m_it != m_mapped_dictionary.end()) 

				// Then push it (suggested word) to vector suggestion
				suggestion.push_back(m_it->first);

			// As for deletion, we do not need to reset \var deletion, 
			// because we just need to scan through the word and delete 
			// character and then return \var deletion
			// Ex: information -> informatio
			//                 -> informati
			//                 -> informat
			//                 -> informa
			//                 -> inform 

			// See Alteration for more info
			m_mapped_dictionary.erase(deletion);
		}

		// 
		// Transposition: swap to adjacent character
		// Ex: information -> infomration
		// 

		// Because we will swap position x and x+1
		// So we just need to scan from 0 to size() - 1
		// to avoid swaping the " " and the last character
		// Ex: if we scan from 0 to size()
		//      information -> informatio n
		for (uint16_t x = 0; x < word.size() - 1; ++x) {
			// Make buffer of word
			std::string transposition = word;

			// Swap character position x and x+1
			std::swap(transposition[x], transposition[x+1]);

			// See explaination in alteration or insertion or deletion 
			// for more info
			m_it = m_mapped_dictionary.find(transposition);
			if (m_it != m_mapped_dictionary.end()) 
				suggestion.push_back(m_it->first);

			// See Alteration for more info
			m_mapped_dictionary.erase(transposition);
		}

	}

	// If matching one word
	else 
		// Then push to the vector "no_typo"
		suggestion.push_back("no_typo");

	// If vector of suggested words is empty
	// which means there exists mistyped word
	// but can not detect suggestions in the dictionary
	if (suggestion.empty())
		suggestion.push_back("No suggestion found.");

	// Return vector of suggested words
	return suggestion;
}


// Constructor with HashTable
SentenceCheck::SentenceCheck
(const std::unordered_map<std::string, int>& mapped_dictionary):
	SpellCheck(mapped_dictionary) {}

// 
//  Split sentence to words and ignore delim(see .hpp file for more info on delim)
//
std::vector<std::string> 
SentenceCheck::split(std::string& str, std::string delim)
{
	// vector of splited words
	std::vector<std::string> splited;

	// get position of first char excluding delimiter
	size_t start = str.find_first_not_of(delim);
	
	// initialise \var end
	size_t end = start;

	// If start position still smaller than size() then keep on spliting
	while (start < str.size()) {
		// Get new end position by finding the next delimiter
		end = str.find_first_of(delim, start);

		// push substr to splited vector
		// get new string from start, with length = end - start
		splited.push_back(str.substr(start, end - start));

		// Get new position of start of next char from old \var end, excluding delim
		start = str.find_first_not_of(delim, end);
	}

	// Return vector of splited words
	return splited;

	// Detail explaination:
	// ex: "i love you"; delim = " "
	//     start = 0; end = 0;
	// starting loop:
	//     end = 2 (because the next " " is at position 2)
	//     substr(0, 2 - 0) which is "i" and push to vector
	//     start = 3 (because the next char is at position 2, excluding delim)
}

//
// Split sentence to words with default delimiter
// See above split for explaination
//
std::vector<std::string> 
SentenceCheck::split(std::string& str)
{
	const std::string delim = "~!@#$%^&*()_+`-=[]\\{}|;':\"<>?,./ ";

	std::vector<std::string> splited;

	size_t start = str.find_first_not_of(delim);
	size_t end = start;

	while (start < str.size()) {
		end = str.find_first_of(delim, start);
		splited.push_back(str.substr(start, end - start));
		start = str.find_first_not_of(delim, end);
	}

	return splited;
}

// 
// Get suggestion map of mistyped sentence 
// See .hpp file for more info on return type and argument
//
std::map<std::string, std::vector<std::string>> 
SentenceCheck::getMap(const std::vector<std::string> tokens)
{
	std::map<std::string, std::vector<std::string>> suggestionMap;
	std::vector<std::string> suggestion;

	// Scan through all elements in vector tokens
	for (uint32_t i = 0; i < tokens.size(); ++i) {
		// get vector of suggestion for a single word \var token.at(i)
		suggestion = SpellCheck::suggest(tokens.at(i));

		// Insert suggested words to map
		//    key                       value
		// ----------------------------------------------
		//   this                      no_typo
		//    ir                         is
		//    an                       no_typo 
		//  efective         elective ejective effective
		//   seacrh                     search
		//  ksdjkjdf              No suggestion found.
		suggestionMap.insert(std::pair<std::string, std::vector<std::string>> 
							 (tokens.at(i), suggestion));
	}

	return suggestionMap;
}

// 
// Convert UPPERCASE to lowercase
// See .hpp file for passed argument and return type
//
std::vector<std::string> 
SentenceCheck::toLower(std::vector<std::string>& tokens)
{
	std::vector<std::string> lowerTokens;
	
	// Get single token from vector
	for (uint32_t i = 0; i < tokens.size(); ++i) {
		std::string bufferLowerString = tokens.at(i);

		// [TODO] Verify this std::transform 
		//        How it works
		//        Does it secure?
		std::transform(bufferLowerString.begin(), 
					   bufferLowerString.end(), 
					   bufferLowerString.begin(), 
					   ::tolower);	

		// Push bash lowercase string to tokens vector
		lowerTokens.push_back(bufferLowerString);
	}

	return lowerTokens;
}