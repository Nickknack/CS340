//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: October 17th, 2015
//Last Modified: October 17th, 2015
//Purpose: 
//***************************************************************************

#include <fstream>
#include "connectedGraph.h"

using namespace std;

int main ()
{
	ifstream input;
	Leader graph[NODEAMOUNT];

	input.open("input.txt");

	if (!(input))
	{
		cout << endl << endl << "ERROR: FILE UNABLE TO OPEN" << endl << endl;
		return 1;
	}

	CarlyRaeConnectedGraph(graph, input);

	return 0;
}