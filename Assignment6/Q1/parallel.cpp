//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: November 25th, 2015
//Last Modified: December 1st, 2015
//Purpose: ReplicatedWorker and it's functions used to create threads
//		   that will do work in parallel. 
//***************************************************************************

#include "parallel.h"


void ReplicatedWorkers(int startTask)
{
	int error; 
	//allocate space for the workers count
	tids = new pthread_t[(NO_OF_WORKERS * NO_OF_WORK_POOLS) + 1];

	if (tids == NULL)
	{
		perror ("Failed to allocate memory for thread IDs");
        exit(1);
	}

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

	PutWork(1, startTask);

	//Create the workers (threads)
	for (int i = 1; i <= (NO_OF_WORK_POOLS * NO_OF_WORKERS); i++)
	{
		if (error = pthread_create (&tids[i], NULL, &Worker, (void *)i))
        {
        	cout << "ERROR: Failed to create thread: " << (strerror(error)) << endl << endl;
        	exit(1);
        }
	}

	//join the workers (threads)
	for (int i = 1; i <= (NO_OF_WORK_POOLS * NO_OF_WORKERS); i++)
	{
		if (error = pthread_join (tids[i], NULL))
        {
        	cout << "ERROR: Failed to join thread: " << (strerror(error)) << endl << endl;
        	exit(1);
        }
	}

	delete [] tids;
}

void PutWork(int workerID, int task)
{
	//The id of the workpool is determined by the value of d for
	//the worker being passed in.
	int workPoolID = d[workerID];
	int idleWorkers;

	Lock(&o);
	if (task == 1)
	{
		cout << "pid: " << pid << " has created task: " << task << " in workPoolID: " << workPoolID << endl;
	}
	else
	{
		cout << "WorkerID: " << workerID << " has created task: " << task << " in workPoolID: " << workPoolID << endl;
	}
	Unlock(&o);

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

	InsertTask(workPoolID, task);

	//increment the value of d so next time this worker adds a task it is to the next workpool
	d[workerID] = (workPoolID % NO_OF_WORK_POOLS) + 1;
}

void InsertTask(int workPoolID, int task)
{
	//Before we can insert the task into the workpool we must first lock the semaphore that
	//is used for controlling access to the workpool variables (semaphore s)
	Lock(&s[workPoolID]);
	tail[workPoolID]++;
	
	//add the task to the end of the FIFO workpool.
	w[workPoolID][tail[workPoolID]] = task;
	//since we are done modifying the workpools we can unlock s
	Unlock(&s[workPoolID]);
}

void *TestFunc(void* id)
{
	int workerID = (int) id;

	Lock(&o);
	cout << "The workerID is: " << workerID << endl;
	Unlock(&o);

	return NULL;
}

void *Worker(void* id)
{
	int task;
	int noOfTasks;
	int workerID = (int) id;

	//each task will create a certain amount of tasks at maximum.
	//this number will be between 1 and 10
	noOfTasks = (rand() % 10) + 1;

	task = GetWork(workerID);

	//while there is still work to do, continue doing work.
	while (task != NO_MORE_WORK)
	{
		DoWork(workerID, task, noOfTasks);
		task = GetWork(workerID);
	}

	Lock(&o);
	cout << "workerID: " << workerID << " has terminated." << endl;
	Unlock(&o);
}

int GetWork(int workerID)
{
	int task, workPoolID, idleWorkers;

	//Determine what workPool the worker works with
	workPoolID = ((workerID - 1) / NO_OF_WORKERS) + 1;

	//The workpool associated with the calculated workPoolID
	//will be modified as well as the emptyWorkPools variable
	//so we need to lock the semaphores for these. 
	Lock(&s[workPoolID]);
	Lock(&e);

	//We are trying to get task from the workpool, so we should
	//decrement the appropriate t. This means that if there are
	//tasks in the workpool t will now represent how many are
	//in the workpool after one has been removed. If no tasks
	//in the workpool then the new value will represent the amount
	//of idle workers.
	t[workPoolID]--;
	idleWorkers = t[workPoolID];

	//If all of the workers are idle then we have an
	//empty workpool and should increment the variable. 
	if (idleWorkers == -NO_OF_WORKERS)
	{
		emptyWorkPools++;

		//If all of the workpools are empty then
		//we need to fill the workpools with the NO_MORE_WORK
		//signal to signify there will no longer be any work
		//and that we are done.
		if (emptyWorkPools == NO_OF_WORK_POOLS)
		{
			Unlock(&e);
			Unlock(&s[workPoolID]);

			for (int i = 1; i <= NO_OF_WORK_POOLS; i++)
			{
				for (int j = 1; j <= NO_OF_WORKERS; j++)
				{
					InsertTask(i, NO_MORE_WORK);
				}
			}
		}
		else
		{
			Unlock(&e);
			Unlock(&s[workPoolID]);
		}
	}
	else
	{
		Unlock(&e);
		Unlock(&s[workPoolID]);
	}

	//Remove the next task from the workpool and return the value.
	task = RemoveTask(workPoolID);
	return (task);
}

void DoWork(int workerID, int task, int& noOfTasks)
{
	int workPoolID;
	struct timespec sleeptime;
	int nextTask = task;

	//initalize the sleep amount to a random amount from 0 to 10 for the seconds and any random amount
	//for the nano seconds. 
	sleeptime.tv_sec = rand() % 10;
    sleeptime.tv_nsec = rand();

	workPoolID = ((workerID - 1) / NO_OF_WORKERS) + 1;

	Lock(&o);
	cout << "WorkerID: " << workerID << " has started task: " << task << " from workPoolID: " << workPoolID << endl;
	Unlock(&o);

	//If the worker hasn't reached it's maximum amount of tasks created yet then create a task.
	if (noOfTasks > 0)
	{
		nextTask++;
		PutWork(workerID, nextTask);
		noOfTasks--;
	}

	//sleep for the amount decided at random
    nanosleep (&sleeptime, NULL);

	Lock(&o);
	cout << "WorkerID: " << workerID << " has finished task: " << task << " from workPoolID: " << workPoolID << endl;
	Unlock(&o);
}

int RemoveTask(int workPoolID)
{
	int task;

	Lock(&s[workPoolID]);

	//Loop until there is work in the work pool to do
	while (1)
	{
		if (w[workPoolID][tail[workPoolID]] == EMPTY)
		{
			Unlock(&s[workPoolID]);
		}
		else
		{
			break;
		}
		Lock(&s[workPoolID]);
	}

	//Get the work from the workpool
	head[workPoolID]++;
	task = w[workPoolID][head[workPoolID]];
	w[workPoolID][head[workPoolID]] = EMPTY;
	Unlock(&s[workPoolID]);
	return task;
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
    if (sem_post (sem) == -1)
    {
    	cout << "ERROR: Thread failed to unlock semaphore" << endl << endl;
        exit (1);
    }
    return;
}