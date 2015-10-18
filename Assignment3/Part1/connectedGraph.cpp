//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: October 17th, 2015
//Last Modified: October 18th, 2015
//***************************************************************************

#include "connectedGraph.h"

#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

void CarlyRaeConnectedGraph(Leader graph[], ifstream& input)
{
	int vert1, vert2;
	Follower* p;

	//Initializes the values in the graph array.
	for (int i = 1; i <= NODEAMOUNT; i++)
	{
		graph[i].vertex = 0;
		graph[i].weight = 0;
		graph[i].firstFollower = NULL;
	}

	//Read in the first value from the file, this will be our leader vertex
	input >> vert1;

	while (input)
	{
		//Read in the second value on the current line of the file; this is a follower of the vertex
		//read into vert1
		input >> vert2;

		//set the value of the vertex to what was read in and point p to the first follower (if any) of the vertex
		graph[vert1].vertex = vert1;
		p = graph[vert1].firstFollower;

		//if the vertex has followers already then traverse the followers until null is reached
		//or until the value is found as one of the followers already
		while (p != NULL)
		{
			if (p->vertex == vert2)
			{
				break;
			}
			p = p->nextFollower;
		}

		//If the value was not found in the vertex's followers then we are going to add it
		//to the followers
		if (p == NULL)
		{
			p = new Follower;
			p->vertex = vert2;
			p->nextFollower = graph[vert1].firstFollower;
			graph[vert1].firstFollower = p;
		}

		//Read in the first value from the next line of the file.
		input >> vert1;
	}
}

void VertexWeightTraversal(Leader graph[])
{
	Follower* p;
	int followerCount;

	//Traverse the followers of each vertex in the graph.
	for (int i = 1; i <= NODEAMOUNT; i++)
	{
		p = graph[i].firstFollower;
		followerCount = 0;

		//traverse each follower, incrementing the followerCount by 1.
		while (p != NULL)
		{
			followerCount++;
			p = p->nextFollower;
		}

		//set the weight value of the leader to 1 divided by the amount of followers
		//it has.
		graph[i].weight = (1 / followerCount);
	}
}

void PrintConnectedGraph(Leader graph[])
{
	Follower* p;

	//Traverse each vertex; print out the vertex followed by each
	//of it's followers.
	for (int i = 1; i <= NODEAMOUNT; i++)
	{
		p = graph[i].firstFollower;
		cout << endl << "page " << graph[i].vertex << endl;

		while (p != NULL)
		{
			cout << "-> page " << p->vertex << endl;
			p = p->nextFollower;
		}
	}
}