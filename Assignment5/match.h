//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: November 12th, 2015
//Last Modified: November 19th, 2015
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

int BoyerMoore (char string[], char pattern[], int matches[], int stringSize, int patternSize, int& matchCount, bool jumpHeur);
//purpose: Finds all of the matching patterns in the string of characters.
//Parameter(s): an array of chars called string which is the string we are searching through
//				an array of chars called pattern which is the pattern we are trying to find in string
//				an array of ints called matches; this contains the indexes for all the matches
//				an int called stringSize indicating the size of the string array
//				an int called patternSize indicating the size of the pattern array
//				an int called matchCount which counts the amount of matches that are made. 
//				a bool valued called jumpHeur which determines wether we are going to use the character
//					jump heuristic or not. 
//Precondition(s): string and pattern have been initialized. 
//Return: returns the amount of comparisions made for the algorithm.
//Side Effect: the matches array will now contain the indexes of all the matches and matchCount will
//			   the amount of matches made. 

int Last (char character, char pattern[], int patternSize, int& compCount);
//purpose: Finds the first occurence of a character in an array of characters working from the last
//		   element to the 0th element.
//Parameter(s): a char called character which is the character we are searching the array for.
//				an array of chars called pattern which is what we are searching.
//              an int called patternSize which is the amount of elements in the array. 
//				an int called compCount which tracks the amount of comparisons made. 
//Return: returns an integer which is the index of the first match of the character. if no match
//		  then a -1 is returned. 
//Side Effect: compCount will be incremented for each comparison made in the algorithm.

int KnuthMorrisPratt (char string[], char pattern[], int matches[], int stringSize, int patternSize, int& matchCount);
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

void Failure(int f[], char pattern[], int patternSize);
//purpose: sets up a failure array (f) that keeps track of substrings within the pattern string. 
//Parameter(s): an array of ints called f. this is the failure array. 
//				an array of chars called pattern which is what we are finding substrings in.
//              an int called patternSize which is the amount of elements in the pattern array. 
//Return: N/A
//Side Effect: the f array will now contain values associated with the substrings found. 

#endif