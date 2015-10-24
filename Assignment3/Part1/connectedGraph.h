//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: October 17th, 2015
//Last Modified: October 18th, 2015
//Purpose: 
//***************************************************************************

#ifndef CONNECTEDGRAPH_H
#define CONNECTEDGRAPH_H

#include <fstream>
#include <iomanip>

using namespace std;

const int NODEAMOUNT = 15;

struct Leader;
struct Follower;

struct Leader
{
	int vertex;
	float weight;
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

void VertexWeightTraversal(Leader graph[]);
	//purpose: Traverses the graph and determines each vertex's weight.
	//Parameter(s): an array of leader called graph; this is the graph we are traversing.
	//Precondition(s): The graph has been built (using CarlyRaeConnectedGraph). 
	//Return: N/A
	//Side Effect: The weight value of each vertex in the graph Array will be set to the appropriate weight
	//             based on the followers of each vertex. 

void PrintConnectedGraph(Leader graph[]);
	//purpose: Traverse the graph and print out the values;
	//Parameter(s): an array of leader called graph; this is the graph we are traversing.
	//Precondition(s): The graph has been built (using CarlyRaeConnectedGraph). 
	//Return: N/A
	//Side Effect: The values of the graph will be printed to the screen.

void CreateTransitionMatrix(Leader graph[], float transitionMatrix[][(NODEAMOUNT + 1)]);
	//purpose: Create a transition matrix of the weights
	//         in the form of a 2D array based on the connected graph;
	//Parameter(s): an array of leader called graph; this is the graph we are traversing.
	//				a 2D array of floats called transtionMatrix which will be the transition
	//				matrix based on the weights of the vertexes in the graph array.
	//Precondition(s): The graph has been built (using CarlyRaeConnectedGraph) and the weights
	//				   have been set with the VertexWeightTraversal function.
	//Return: N/A
	//Side Effect: transitionMatrix array will contain the approriate weight values.

void WriteTransitionMatrix(float transitionMatrix[][(NODEAMOUNT + 1)], ofstream& outFile);
	//purpose: Write the transition matrix to an output file.
	//Parameter(s): a 2D array of floats which is the transitionMatrix
	//Precondition(s): The transitionMatrix has been built with the CreatetransitionMatrix function.
	//Return: N/A
	//Side Effect: the output file will contain the transition

#endif