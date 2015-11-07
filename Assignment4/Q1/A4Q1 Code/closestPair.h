//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: October 30th, 2015
//Last Modified: October 30th, 2015
//Purpose: Functions involved with finding the closest pair amongst a group
//		   of points.
//***************************************************************************

#ifndef CLOSESTPAIR_H
#define CLOSESTPAIR_H

#include <fstream>
#include <cmath>
#include <iostream>

using namespace std;

struct Point
{
	int x;
	int y;
};

struct ClosestPair
{
	float dMin;
	Point P1;
	Point P2;
};

ClosestPair CallFindClosestPair(ifstream& inFile, int n);
//purpose: Does initialization (sorting, building pX and pY etc.) before calling the FindClosestPair function
//Parameter(s): an ifstream called inFile which is the input file that contains the points
//			    an int called n which is the amount of points in the file that the user entered. 
//Precondition(s): The input file being passed in has been opened and n has been set to the appropriate variable. 
//Return: a ClosestPair value which will be the two closest points in the list of points in the passed in file. 
//Side Effect: The contents of the file will have been read. 

ClosestPair FindClosestPair(Point* pX, Point* pY, int n);
//purpose: Finds the closest pairs in the points sorted by x into pX and into pY. 
//Parameter(s): an array of Points called pX containing all the sets of points sorted by x (and then by y when x's are equal)
//				an array of Points called pY containing all the sets of points sorted by y
//			    an int called n which is how many points there are.
//Precondition(s): pX and pY have been sorted accordingly.
//Return: a ClosestPair value containing the closest pair in the set of points. 
//Side Effect: N/A

ClosestPair BruteForce(Point* pX, int n);
//purpose: Bruteforces the closest points. 
//Parameter(s): an array of Points called pX containing all the sets of points sorted by x (and then by y when x's are equal)
//			    an int called n which contains the amount of points in the set of points.
//Precondition(s): pX must be sorted accordingly and n must be <= 3
//Return: Returns a ClosestPair containing the closest pair of points in the set.k 
//Side Effect: N/A

ClosestPair Min(ClosestPair& clPL, ClosestPair& clPR);
//purpose: Find the closest pair of points between two closestPairs
//Parameter(s): a ClosestPair point called clPL which is the closest pair from the left partion
//			    a ClosestPair point called clPR which is the closest pair from the right partition
//Precondition(s): N/A
//Return: returns a ClosestPair containing the closest pair. 
//Side Effect: The array called graph being passed in will now contain the graph that was generated based
//             on the input file.

float Dist (Point& p1, Point& p2);
//purpose: finds the distance between two points. 
//Parameter(s): a Point called p1 which is the first point
//				a Point called p2 which is the second point. 
//Precondition(s): N/A
//Return: returns a float value which is the distance between the two points. 
//Side Effect: N/A

void InsertionSort(Point* p, int n, char valueToSort);
//purpose: Sorts the Point array passed in either by x or by y values.
//Parameter(s): an array of Points called p which are the values to be sorted. 
//			    an int called n, which contains the amount of points in p
//              a char called valuetoSort; indicates if we are sorting by x or by y values. 
//Precondition(s): p has been filled. 
//Return: N/A
//Side Effect: p will have it's contents sorted. 

#endif
