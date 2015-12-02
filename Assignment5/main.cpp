//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: November 12th, 2015
//Last Modified: November 19th, 2015
//Purpose: Run a string of characters through the 4 string pattern matching
//		   Algorithms and count the amount of comparisons. 
//***************************************************************************

#include <iostream>
#include <fstream>
#include <string>
#include "match.h"

using namespace std;

const int MAX_ARRAY = 9000;

int main ()
{
	//Variable Declerations
	char string[MAX_ARRAY];
	int matches[MAX_ARRAY];
	char pattern[MAX_ARRAY];
	char bufferChar;
	ifstream input, inPattern;
	int stringSize, patternSize;
	int matchCount = 0;
	int comps = 0;


	//opening and testing the files
	input.open("text.txt");
	inPattern.open("patterns.txt");

	if (!input)
	{
		cout << endl << endl << "ERROR: Unable to open input.txt" << endl << endl;
		return 1;
	}

	if (!inPattern)
	{
		cout << endl << endl << "ERROR: Unable to open pattern.txt" << endl << endl;
		return 1;
	}

	stringSize = 0;
	
	//Loop through the file reading in the next character until the end of the file
	//is reached or the maximum size of the array is reached. 
	input.get(bufferChar);

	//read in the string from the file.
	while (!(input.eof()) && (stringSize < MAX_ARRAY))
	{
		string[stringSize++] = bufferChar;
		input.get(bufferChar);
	}

	//Each line of the pattern file is a new patter for matching with the string. 
	//While we haven't reached the end of pattern file we are going to read in 1 full line
	//from the pattern file (until a newline character is reached) and then we will run the
	//pattern matching algorithms on the line. We continue reading in lines from the file and then
	//running the algorithms on the line until we have reached the end of the file. 
	inPattern.get(bufferChar);
	while (!(inPattern.eof()))
	{
		patternSize = 0;

		while ((bufferChar != '\n') && (patternSize < MAX_ARRAY))
		{
			pattern[patternSize++] = bufferChar;
			inPattern.get(bufferChar);
		}

		cout << endl << "Pattern matching on: ";

		for (int i = 0; i < patternSize; i++)
		{
			cout << pattern[i];
		}

		//***************START: BRUTE FORCE***************

		//Use the BruteForce algorithm for pattern matching.
		comps = BruteForce(string, pattern, matches, stringSize, patternSize, matchCount);

		//display the results.
		cout << endl << "*****BRUTE FORCE****" << endl << endl;
		cout << "There are " << matchCount << " matches." << endl;

		if (matchCount > 0)
		{
			cout << "matches at:" << endl;
		}

		for (int i = 0; i < matchCount; i++)
		{
			cout << "    position " << matches[i] << endl;
		}

		cout << comps << " comparisons where made." << endl << endl;

		//***************END: BRUTE FORCE***************

		//reset matchCount to 0 for the next patternMatching algorithm.
		matchCount = 0;

		//***************START: BOYER-MOORE***************

		//Use the Boyer-Moore algorithm for pattern matching
		comps = BoyerMoore(string, pattern, matches, stringSize, patternSize, matchCount, true);

		//display the results.
		cout << endl << "*****BOYER-MOORE****" << endl << endl;
		cout << "There are " << matchCount << " matches." << endl;

		if (matchCount > 0)
		{
			cout << "matches at:" << endl;
		}

		for (int i = 0; i < matchCount; i++)
		{
			cout << "    position " << matches[i] << endl;
		}

		cout << comps << " comparisons where made." << endl << endl;

		//***************END: BOYER-MOORE***************

		//reset matchCount to 0 for the next patternMatching algorithm.
		matchCount = 0;

		//***************START: BOYER-MOORE(without the character jump heuristic)***************
		comps = BoyerMoore(string, pattern, matches, stringSize, patternSize, matchCount, false);

		//display the results.
		cout << endl << "*****BOYER-MOORE (without Character Jump Heuristic)****" << endl << endl;
		cout << "There are " << matchCount << " matches." << endl;

		if (matchCount > 0)
		{
			cout << "matches at:" << endl;
		}

		for (int i = 0; i < matchCount; i++)
		{
			cout << "    position " << matches[i] << endl;
		}

		cout << comps << " comparisons where made." << endl << endl;

		//***************END: BOYER-MOORE(without the character jump heuristic)***************
		matchCount = 0;

		//***************START: KNUTH-MORRIS-PRATT***************
		comps = KnuthMorrisPratt(string, pattern, matches, stringSize, patternSize, matchCount);

		//display the results.
		cout << endl << "*****KNUTH-MORRIS-PRATT****" << endl << endl;
		cout << "There are " << matchCount << " matches." << endl;

		if (matchCount > 0)
		{
			cout << "matches at:" << endl;
		}

		for (int i = 0; i < matchCount; i++)
		{
			cout << "    position " << matches[i] << endl;
		}

		cout << comps << " comparisons where made." << endl << endl;

		//***************END: KNUTH-MORRIS-PRATT***************

		matchCount = 0;

		inPattern.get(bufferChar);
	}

	return 0;
}