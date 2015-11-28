//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: November 25th, 2015
//Last Modified: November 25th, 2015
//Purpose: ReplicatedWorker and it's functions used to create threads
//		   that will do work in parallel. 
//***************************************************************************

#ifndef PARALLEL_H
#define PARALLEL_H

#include <iostream>
using namespace std;

const int NO_OF_WORK_POOLS = 3;
const int NO_OF_WORKERS = 5;
const int EMPTY = -999;
//since the amount of tasks being generated is between 10 and 100
//there will never be 500 tasks in a workpool; so 500
//is a safe size to make the workpool arrays where we are working
//with essentially inifitly large workpools.
const int LARGE_WORKPOOL_SIZE = 500;

//when t[i] >= 0 it represents the number of tasks
//in the workpool i. When it is less than 0 it represents
//the number of idle workers for that workpool. 
extern int t[NO_OF_WORK_POOLS+1];
//the amount of tasks that will be created
extern int w[NO_OF_WORK_POOLS+1][LARGE_WORKPOOL_SIZE];
//head and tail are the the indexes of the current
//head and tail for each of the workpools w.
extern int head[NO_OF_WORK_POOLS+1];
extern int tail[NO_OF_WORK_POOLS+1];

//d says which workpool the next task created should be inserted to
extern int d[(NO_OF_WORK_POOLS * NO_OF_WORKERS)+1];

//emptyWorkPools is the amount of currently empty work pools
extern int emptyWorkPools;


//the amount of tasks that will
//be created during the run of this program
//and is a random number between 10 and 100.
extern int maxTasks;

void ReplicatedWorkers(int startTask);
//purpose: Initalize and start the replicated workers process
//Parameter(s): an integer called startTask which is the first task to be started.
//Precondition(s): N/A
//Return: N/A.
//Side Effect: The tasks will be run and completed.


#endif