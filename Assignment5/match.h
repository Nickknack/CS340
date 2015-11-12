//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: November 12th, 2015
//Last Modified: November 12th, 2015
//Purpose: pattern matching algorithms
//***************************************************************************

#ifndef MATCH_H
#define MATCH_H

#include <string>
#include <iostream>

using namespace std;

int BruteForce(char string[], char pattern[], int matches[], int stringSize, int patternSize, int& matchCount);
//purpose: Finds all of the matching patterns in the string of characters.
//Parameter(s): an array of chars called string which is the string we are searching through
//				an array of chars called pattern which is the pattern we are trying to find in string
//				an array of ints called matches; this contains the indexes for all the matches
//				an int called stringSize indicating the size of the string array
//				an int called patternSize indicating the size of the pattern array
//				an int called matchCount which counts the amount of matches that are made. 
//Precondition(s): string and pattern have been initialized. 
//Return: returns the amount of comparisions made for the algorithm.
//Side Effect: the matches array will now contain the indexes of all the matches and matchCount will
//			   the amount of matches made. 

#endif