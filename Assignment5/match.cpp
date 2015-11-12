//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: November 12th, 2015
//Last Modified: November 12th, 2015
//Purpose: pattern matching algorithms
//***************************************************************************

#include  "match.h"

int BruteForce(char string[], char pattern[], int matches[], int stringSize, int patternSize, int& matchCount)
{
	int j;
	int compCount = 0;

	//This will loop and check the first character in the pattern
	//agains the first character of the string. If they match it will
	//check the second character in the patern with the second character
	//of the string. It will do this until either the end of the pattern
	//is reached (a pattern match!) or one of the characters don't match.
	for (int i = 0; i <= (stringSize - patternSize); i++)
	{
		j = 0;

		//This while loop is checking the first character in the pattern
		//against the current string character; if they match it will check
		//the next character and so on until a patern match or the characters
		//don't match.
		while ((j < patternSize) && (string[i + j] == pattern[j]))
		{
			j++;
			compCount++;
		}

		//if j == patternSize it means we had a match
		//otherwise the loop was never entered due to a
		//failed comparison which we still need to count.
		if (j == patternSize)
		{
			matches[matchCount++] = i;
		}
		else
		{
			compCount++;
		}
	}

	return compCount;
}