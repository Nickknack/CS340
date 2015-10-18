//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: October 17th, 2015
//Last Modified: October 17th, 2015
//Purpose: 
//***************************************************************************

#ifndef CONNECTEDGRAPH_H
#define CONNECTEDGRAPH_H

#include <fstream>
#include <iomanip>

using namespace std;

const int NODEAMOUNT = 15;

struct Leader
{
	int vertex;
	Follower* firstFollower;
};

struct Follower
{
	int vertex;
	Follower* nextFollower;
};

void CarlyRaeConnectedGraph(Leader graph[], ifstream& input);
	//purpose: Initialize the connected node with the appropiate value and followers.
	//Parameter(s): an array of the type Leader called graph an input file called input; the format is two 
	//			    numbers on a line seperated by a space. These two numbers are the connected vertex's and each line 
	//              represents an edge of the graph.
	//Precondition(s): The input file being passed in has been opened. 
	//Return: N/A
	//Side Effect: The array called graph being passed in will now contain the graph that was generated based
	//             on the input file.
#endif