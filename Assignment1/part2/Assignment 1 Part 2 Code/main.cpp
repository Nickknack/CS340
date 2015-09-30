//****************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibel, Evan Boyle
//Created: September 12th, 2015
//Last Modified: September 14th, 2015
//Purpose: generates m trees with n nodes and determines the average depths
//         outputing the values to a file. 
//***************************************************************************
#include "BinarySearchTree.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

int main ()
{
	ofstream outputFile; //The file to output the comma seperated value.

	//Seed random to the current time.
	srand(time(NULL));

	//Opening the output file; if it can't be opened output an error message and 
	//exit program.
	outputFile.open("AverageHeights.txt");

	if (outputFile.fail())
	{
		cout << "ERROR: File couldn't open." << endl;
		return 1;
	}

	//Output the values of n as header in the file
	outputFile << "4, 32, 256, 2048" << endl;

	//Calculate the averageDepth for the different values of n and m and output the result
	//to the output file.
	outputFile << AverageDepthOfMTreesNNodes(4, 8) << ", ";
	outputFile << AverageDepthOfMTreesNNodes(32, 64) << ", ";
	outputFile << AverageDepthOfMTreesNNodes(256, 512) << ", ";
	outputFile << AverageDepthOfMTreesNNodes(2048, 4096);

	//Nothing more to output; close the output file.
	outputFile.close();

	return 0;
}