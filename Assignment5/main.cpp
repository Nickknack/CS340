//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: November 12th, 2015
//Last Modified: November 12th, 2015
//Purpose: Run a string of characters through the 4 string pattern matching
//		   Algorithms and count the amount of comparisons. 
//***************************************************************************

#include <iostream>
#include <fstream>
#include <string>
#include "match.h"

using namespace std;

const int MAX_ARRAY = 500;
const int PATTERN_SIZE = 4;

int main ()
{
	//Variable Declerations
	char string[MAX_ARRAY];
	int matches[MAX_ARRAY];
	char pattern[PATTERN_SIZE] {'a', 'b', 'c', 'd'};
	char bufferChar;
	ifstream input;
	int stringSize;
	int matchCount = 0;
	int comps = 0;


	//opening and testing the file
	input.open("input.txt");

	if (!input)
	{
		cout << endl << endl << "ERROR: Unable to open file." << endl << endl;
		return 1;
	}

	stringSize = 0;
	
	//Loop through the file reading in the next character until the end of the file
	//is reached or the maximum size of the array is reached. 
	input.get(bufferChar);

	while (!(input.eof()) && (stringSize < MAX_ARRAY))
	{
		//If the character read in isn't a whitespace, put it in the array
		if (bufferChar != ' ')
		{
			string[stringSize++] = bufferChar;
		}
		input.get(bufferChar);
	}

	comps = BruteForce(string, pattern, matches, stringSize, PATTERN_SIZE, matchCount);

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

	return 0;
}