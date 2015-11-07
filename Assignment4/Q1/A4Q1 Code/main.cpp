//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: October 30th, 2015
//Last Modified: October 30th, 2015
//Purpose: Takes an input file of points and then finds the two closest points
//***************************************************************************

#include "closestPair.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main ()
{
	//Variable declerations
	ifstream inFile;
	string fileName;
	int n;
	ClosestPair clP;

	//Prompt user for the name of a file.
	cout << endl << "input Filename: ";
	cin >> fileName;

	//Convert the file to a c_string and open it
	inFile.open(fileName.c_str());

	if (!inFile)
	{
		cout << endl << endl << "ERROR: Unable to open file" << endl << endl;
		return 1;
	}

	//Ask the user for the amount of points the file contains. 
	cout << endl << "how many points are there: ";
	cin >> n;

	//call the CallFindClosestPair function
	clP = CallFindClosestPair(inFile, n);

	//Print out the closest pairs. 
	cout << endl << endl << "The Closest Pair: (" << clP.P1.x << ", " << clP.P1.y << ") & (" << clP.P2.x << ", " << clP.P2.y << ")" << endl << endl;

	return 0;
}