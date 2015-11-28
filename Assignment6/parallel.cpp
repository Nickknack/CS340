//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: November 25th, 2015
//Last Modified: November 25th, 2015
//Purpose: 
//***************************************************************************

#include "parallel.h"

void ReplicatedWorkers(int startTask)
{
	//For testing purposes. 
	cout << "The value of startTask is: " << startTask << endl;
	cout << "The value of maxTasks is: " << maxTasks << endl << endl;

	for (int i = 1; i <= NO_OF_WORK_POOLS; i++)
	{
		//initalize the amount of work in the workpools to 0
		t[i] = 0;
		//initialize the work pools to be empty.
		w[i][0] = EMPTY;

		//Initalize the values in d to be the appropriate value
		for (int j = ((i - 1) * NO_OF_WORKERS + 1); j <= (i * NO_OF_WORKERS); j++)
		{
			d[j] = i % (NO_OF_WORK_POOLS + 1);
		}

		//since the workpools are initialized to EMPTY the head and tail should 
		//point to the EMPTY value.
		head[i] = 0;
		tail[i] = 0;
	}

	d[1] = 1;

	//initalize the value of emptyWorkPools to 0
	emptyWorkPools = 0;

	//***FOR TESTING***//
	for (int i = 1; i <= NO_OF_WORK_POOLS; i++)
	{
		cout << "The value of t[" << i << "] is: " << t[i] << endl;
		cout << "The value of w[" << i <<"][0] is: " << w[i][0] << endl;

		for (int j = ((i - 1) * NO_OF_WORKERS + 1); j <= (i * NO_OF_WORKERS); j++)
		{
			cout << "The value of d[" << j << "] is: " << d[j] << endl;
		}

		cout << "The value of head[" << i << "] is: " << head[i] << endl;
		cout << "The value of tail[" << i << "] is: " << tail[i] << endl;
	}
}