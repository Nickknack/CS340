//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: October 17th, 2015
//Last Modified: October 18th, 2015
//Purpose: 
//***************************************************************************

#include <fstream>
#include <iostream>
#include "connectedGraph.h"

using namespace std;

int main ()
{
	ifstream input;
	Leader graph[(NODEAMOUNT+1)];

	input.open("input.txt");

	if (!(input))
	{
		cout << endl << endl << "ERROR: FILE UNABLE TO OPEN" << endl << endl;
		return 1;
	}
	CarlyRaeConnectedGraph(graph, input);
	VertexWeightTraversal(graph);
	PrintCoonnectedGraph(graph);

	return 0;
}