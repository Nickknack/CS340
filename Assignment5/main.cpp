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

using namespace std;

const int MAX_ARRAY = 500;

int main ()
{
	char string[MAX_ARRAY];
	char bufferChar;
	ifstream input;
	int stringSize;

	input.open("input.txt");

	if (!input)
	{
		cout << endl << endl << "ERROR: Unable to open file." << endl << endl;
		return 1;
	}

	stringSize = 0;
	
	//Loop through the file reading in the next character until the end of the file
	//is reached or the maximum size of the array is reached. 
	while (!(input.eof()) && (stringSize < MAX_ARRAY))
	{
		input.get(bufferChar);

		//If the character read in isn't a whitespace, put it in the array
		if (bufferChar != ' ')
		{
			string[stringSize++] = bufferChar;
		}
	}

	return 0;
}