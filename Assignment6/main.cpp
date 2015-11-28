//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: November 25th, 2015
//Last Modified: November 25th, 2015
//Purpose: Determine a random amount of tasks to accomplish and run them using
//		   threads.
//***************************************************************************

using namespace std;

#include <time.h>
#include <iostream>
#include <stdlib.h>
#include "parallel.h"

//the amount of tasks that will be created
int maxTasks;

//when t[i] >= 0 it represents the number of tasks
//in the workpool i. When it is less than 0 it represents
//the number of idle workers for that workpool. 
int t[NO_OF_WORK_POOLS+1];
//the amount of tasks that will be created
int w[NO_OF_WORK_POOLS+1][LARGE_WORKPOOL_SIZE];
//head and tail are the the indexes of the current
//head and tail for each of the workpools w.
int head[NO_OF_WORK_POOLS+1];
int tail[NO_OF_WORK_POOLS+1];

//d says which workpool the next task created should be inserted to
int d[(NO_OF_WORK_POOLS * NO_OF_WORKERS)+1];

//emptyWorkPools is the amount of currently empty work pools
int emptyWorkPools;

int main ()
{
	srand(time(NULL));
	//a random amount of tasks will be generated
	//anywhere from 10 to 100
	maxTasks = rand() % 100 + 10;

	ReplicatedWorkers(1);

	cout << "End of the program has been reached" << endl << endl;
	return 0;
}