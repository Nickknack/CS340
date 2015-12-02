//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: November 25th, 2015
//Last Modified: December 1st, 2015
//Purpose: Determine a random amount of tasks to accomplish and run them using
//		   threads.
//***************************************************************************

using namespace std;

#include <time.h>
#include <iostream>
#include <stdlib.h>
#include "parallel.h"
#include <semaphore.h>

//the amount of tasks that will be created
int maxTasks;

//when t[i] >= 0 it represents the number of tasks
//in the workpool i. When it is less than 0 it represents
//the number of idle workers for that workpool. 
int t[NO_OF_WORK_POOLS+1];
//FIFO of tasks waiting to be executed;
//essentially the workpools of tasks.
int w[NO_OF_WORK_POOLS+1][LARGE_WORKPOOL_SIZE];
//head and tail are the the indexes of the current
//head and tail for each of the workpools w.
int head[NO_OF_WORK_POOLS+1];
int tail[NO_OF_WORK_POOLS+1];

//d says which workpool the next task created should be inserted to
int d[(NO_OF_WORK_POOLS * NO_OF_WORKERS)+1];

//emptyWorkPools is the amount of currently empty work pools
int emptyWorkPools;

//an array of semaphores for accessing the values of t
sem_t s[NO_OF_WORK_POOLS+1];
//a semephore for accessing the emptyWorkPools variable
sem_t e;
//a semephore for accessing printing to the output. 
sem_t o;

pthread_t *tids;

int main ()
{
	srand(time(NULL));
	//a random amount of tasks will be generated
	//anywhere from 10 to 100
	maxTasks = rand() % 100 + 10;

	//initialize all of the s[i] semaphores
	for (int i = 1; i <= NO_OF_WORK_POOLS; i++)
	{
		Init(&s[i]); 
	}
	//initalize the e semephore
	Init(&e);
	//initalize the o semaphore
	Init(&o);

	//call replicated workers with the first task being
	//task 1.
	ReplicatedWorkers(1);

	//Before the program ends we need to destroy the semephores we created. 
	for (int i = 1; i <= NO_OF_WORK_POOLS; i++)
	{
		Destroy(&s[i]); 
	}
	Destroy(&e);
	Destroy(&o);

	cout << "End of the program has been reached" << endl << endl;
	return 0;
}