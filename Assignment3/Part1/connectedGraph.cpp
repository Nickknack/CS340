//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: October 17th, 2015
//Last Modified: October 17th, 2015
//***************************************************************************

#include "connectedGraph.h"

#include <fstream>
#include <iomanip>

using namespace std;

void CarlyRaeConnectedGraph(ifstream& input)
{
	int vert1, vert2;
	Follower* p;

	for (int i = 1; i < NODEAMOUNT; i++)
	{
		graph[i].vertex = 0;
		graph[i].firstFollower = NULL;
	}

	input >> vert1;

	while (input)
	{
		input >> vert2;
		p = graph[vert1].firstFollower;

		while (p != NULL)
		{
			if (p->vertex == vertex2)
			{
				break;
			}
			p = p->nextFollower;
		}
		if (p == NULL)
		{
			p = new Follower;
			p->vertex = vertex2;
			p->nextFollower = graph[vertex1].firstFollower;
			graph[vertext1].firstFollower = p;

			p = new Follower;
			p->vertex = vertex1;
			p->nextFollower = graph[vertex2].firstFollower;
			graph[vertext2].firstFollower = p;
		}

		input >> x;
	}
}