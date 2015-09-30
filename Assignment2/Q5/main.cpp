//****************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibel, Evan Boyle
//Created: September 23rd, 2015
//Last Modified: September 27th, 2015
//Purpose: Topologically sort the values found in the CS_Prerequisites.txt
//		   file and print out the values after the sort. 
//***************************************************************************

#include "topological.h"
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	ifstream input;

	input.open("CS_Prerequisites.txt");

	if (!(input))
	{
		cout << endl << endl << "ERROR: FILE UNABLE TO OPEN" << endl << endl;
		return 1;
	}

	TopologicalSort(input);

	return 0;
}