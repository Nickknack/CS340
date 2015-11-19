//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: November 12th, 2015
//Last Modified: November 19th, 2015
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

int BoyerMoore (char string[], char pattern[], int matches[], int stringSize, int patternSize, int& matchCount, bool jumpHeur)
{
	//Initalize variables
	//i and j are initialized to patternSize - 1 because we are looking at
	//the end of the pattern and working towards the front. 
	int i = patternSize - 1;
	int j = patternSize - 1;
	int compCount = 0;

	do
	{
		//check the current character on the string with the
		//current character on the pattern. and increment the comparison counter.
		compCount++;
		if (pattern[j] == string[i])
		{
			//If there is a match when j is 0 then we have a match; record the index
			//of the match in the matches array and then increment the match counter. 
			if (j == 0)
			{
				matches[matchCount++] = i;

				i = i + patternSize - j;
				j = patternSize - 1;
			}
			//If there is a match but j isn't 0 we need to check the next character in the
			//pattern with the next character of the string so decrement i and j.
			else
			{
				i--;
				j--;
			}
		}
		//If there isn't a match determine the appropriate i and j values for the next pattern
		//match test. 
		//If jumpHeur is true the character jump heuristic is used for i; take the character that
		//caused the mismatch and check wether that character occurs in the pattern. If the
		//character doesn't occur in p then set i so that p is shifted past t[i] but if there is 
		//a match set i so that the mismatched character in the string lines up with the occurence 
		//of the character in the pattern. 
		else
		{
			if (jumpHeur == true)
			{
				i = i + patternSize - min(j, 1 + Last(string[i], pattern, patternSize, compCount));
			}
			else
			{
				i = i + patternSize - j;
			}

			j = patternSize - 1;
		}
	} while (i < stringSize);

	return compCount;
}

int Last (char character, char pattern[], int patternSize, int& compCount)
{
	//character is the character that failed the match test.
	//search from the end of the pattern for the first occurence of that
	//character and return the index. If no match, return -1.
	for (int i = (patternSize - 1); i >= 0; i--)
	{
		compCount++;
		if (character == pattern[i])
		{
			return i;
		}
	}
	return -1;
}

int KnuthMorrisPratt (char string[], char pattern[], int matches[], int stringSize, int patternSize, int& matchCount)
{
	//initalize variables
	int f[patternSize];
	int i = 0;
	int j = 0;
	int compCount = 0;

	//initalize the failure array. 
	Failure(f, pattern, patternSize);

	//loop through the string and compare first character of the pattern with the first character
	//of the string. if they match increment the indexes. otherwise increment just the string's index
	//and start comparing the pattern to the next character in the string. Continue this until a match
	//or mismatch is found. 
	while (i < stringSize)
	{
		compCount++;
		if (pattern[j] == string[i])
		{
			if (j == (patternSize - 1))
			{
				matches[matchCount++] = (i - patternSize + 1);
			}
			i++;
			j++;
		}
		//if a mismatch is found on a character in the pattern that isn't the first then we can use the failure
		//array to determine if we can set the index for the pattern to something higher than 0.
		else if (j > 0)
		{
			j = f[j - 1];
		}
		else
		{
			i++;
		}
	}
	return compCount;
}

void Failure(int f[], char pattern[], int patternSize)
{
	//initialize variables
	int i = 1;
	int j = 0;

	//initalize the failure value at index 0 to 0 as there aren't any characters
	//before that one
	f[0] = 0;

	//loop through the pattern array; if a value matches that of the first value set the equivelent
	//position in f to 1; compare the next value of the pattern with the 2nd value of the pattern
	//and if they match set the equivelent position in f to 2. Continue doing this until a mismatch
	//and then go back to comparing with the first value in pattern. 
	while (i < patternSize)
	{
		if (pattern[j] == pattern[i])
		{
			f[i] = j + 1;
			i++;
			j++;
		}
		else if (j > 0)
		{
			j = f[j - 1];
		}
		else
		{
			f[i] = 0;
			i++;
		}
	}

}
