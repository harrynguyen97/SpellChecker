#include "main.hpp"

int main()
{
	// HashTable contains English words
	unordered_map<string, int> engDictHashTable;

	// Map contains suggested words for a mistyped sentence
	std::map<std::string, std::vector<std::string>> suggestionMap;

	// Vector of tokens splited from sentence
	std::vector<std::string> tokens; 

	// Path to dictionary file
	// [WARNING] If there are any changes to this path, 
	//           remember to change it in unit test .cpp file too
	string path_to_file = "bin/words.txt";
	
	string sentence;


	Database engDict(path_to_file);
	cout << "Loading...\n";

	// Hash english dictionary file to endDictHashTable
	engDictHashTable = engDict.hashIntoTable();

	// Show info about total number of words in dictionary
	cout << "Database contains: " << engDict.getNumberOfWords(engDictHashTable) 
		 << " words" << endl;
	
	while (true) {
		// Get sentence from user's input
		// [WARNING] Sometimes the input sentence just passed through 
		//           and do not do anything for checking
		//           Ex: >> This is a sentence
		//               >> This is a sentence too, after passed
		// [REASON] This problem occurs due to "\n" at the last char of input
		// 			and the OS interpret this as "enter"
		// [SOLVING] Can be fixed by using cin.ignore() but it just ignores 
		//           the first letter of every sentence
		//           Ex: input: this is -> output: his is
		// 			 This may be because the default argument of cin.ignore() 
		//           is 1, and it just ignores 1 char
		// Need to solve this  
		cout << ">> ";
		getline(cin, sentence);
		
		// Initialise GoogleCheck with HashTable = endDictHashTable
		SentenceCheck GoogleCheck(engDictHashTable);

		// split sentence to words with default delim
		tokens = GoogleCheck.split(sentence);
		
		// convert any uppercase to lowercase
		tokens = GoogleCheck.toLower(tokens);

		// get suggestion map for every mistyped word in the sentence
		suggestionMap = GoogleCheck.getMap(tokens);
		
		// Flag for indicating that there is no typo at all
		int flagTypo = 1;

		// Iterate through suggestion map
		for (auto it = suggestionMap.begin(); it != suggestionMap.end(); ++it) {
			
			// If the value of map (see SpellCheck.cpp) is not "no_typo"
			// which means <suggested_words> or "No suggestion found."
			if (it->second.at(0) != "no_typo") {
				// Then turn off flagTypo
				flagTypo = 0;

				cout << "You mistyped at \"" << it->first << "\"" << ": ";
				for (uint16_t i = 0; i < it->second.size(); ++i) 
					cout << it->second.at(i) << "  ";
				
				cout << endl;
			}
		}

		// Check flagTypo
		if (flagTypo != 0)  
			cout << "No typo found.\n";

		cout << endl;
	}
	
	return EXIT_SUCCESS;
}


