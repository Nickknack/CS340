//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: November 25th, 2015
//Last Modified: November 28th, 2015
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
	cout << "the value of emptyWorkPools: " << emptyWorkPools << endl << endl;

	PutWork(1, startTask);

	//*****FOR TESTING*******
	for (int i = 1; i <= NO_OF_WORK_POOLS; i++)
	{
		cout << "The value of t[" << i << "] is: " << t[i] << endl;

		for (int j = ((i - 1) * NO_OF_WORKERS + 1); j <= (i * NO_OF_WORKERS); j++)
		{
			cout << "The value of d[" << j << "] is: " << d[j] << endl;
		}
	}
	cout << "the value of emptyWorkPools: " << emptyWorkPools << endl << endl;
}

void PutWork(int workerID, int task)
{
	//The id of the workpool is determined by the value of d for
	//the worker being passed in.
	int workPoolID = d[workerID];
	int idleWorkers;

	//While we are putting work into the workpool lock the t for the workpool we are 
	//working with and lock e.
	Lock(&s[workPoolID]);
	Lock(&e);

	//Since we are adding a task to the workpool we should increment the tasks in
	//workpool counter for the workpool we are using.
	//if the value  is >= 0 that means there aren't currently any idle workers
	//and therefore the task is going into the workpool
	//if the value is < 0 then there is an idle worker and therefore we are
	//removing a worker from the idle worker counter because it will pick up
	//the task.
	t[workPoolID]++;

	//since t is also the idle worker count when the value is < 0 we can set the value of 
	//idleWorkers to the value of t.
	idleWorkers = t[workPoolID];

	//*NOTE* Not sure why we do this; going to ask Hilderman about it
	if (idleWorkers == (-NO_OF_WORKERS + 1))
	{
		emptyWorkPools--;
	}

	//Done working with t[workPoolID] and emptyWorkPools so can unlock semaphores now
	Unlock(&s[workPoolID]);
	Unlock(&e);

	//InsertTask function not created yet
	//InsertTask(workPoolID, task);

	//increment the value of d so next time this worker adds a task it is to the next workpool
	d[workerID] = workPoolID % NO_OF_WORK_POOLS + 1;
}


//******Semaphore functions***********
void Init(sem_t *sem)
{
    if (sem_init (sem, 0, 1) == -1)
    {
        perror ("ERROR: failed to initialize semaphore");
        exit(1);
    }
}

void Destroy(sem_t *sem)
{
    if (sem_destroy (sem) == -1)
    {
        perror ("ERROR: Failed to destroy semaphore");
        exit(1);
    }
}

void Lock(sem_t *sem)
{
    while (sem_wait (sem) == -1)
    {
        if(errno != EINTR)
        {
        	cout << "ERROR: Thread failed to lock semaphore" << endl << endl;
            exit(1);
        }
    }
}

void Unlock(sem_t *sem)
{
    if (sem_destroy (sem) == -1)
    {
        perror ("ERROR: Failed to destroy semaphore");
        exit (1);
    }
}