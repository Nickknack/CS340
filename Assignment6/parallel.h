//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: November 25th, 2015
//Last Modified: December 1st, 2015
//Purpose: ReplicatedWorker and it's functions used to create threads
//		   that will do work in parallel. 
//***************************************************************************

#ifndef PARALLEL_H
#define PARALLEL_H

#include <iostream>
#include <semaphore.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

using namespace std;

const int NO_OF_WORK_POOLS = 3;
const int NO_OF_WORKERS = 5;
const int NO_MORE_WORK = -777;
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

//an array of semaphores for accessing the values of t
extern sem_t s[NO_OF_WORK_POOLS+1];
//a semephore for accessing the emptyWorkPools variable
extern sem_t e;
//a semephore for accessing printing to the output. 
extern sem_t o;

extern pthread_t *tids;



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

void PutWork(int workerID, int task);
//purpose: Puts work into a workpool
//Parameter(s): an integer called workerID which indicates the worker who is putting the task into
//				the workpool and an integer called task which is the task to be inserted
//Precondition(s): N/A
//Return: N/A.
//Side Effect: Ta task will be put into the appropriate workpool

void InsertTask(int workPoolID, int task);
//purpose: Called by PutWork; Puts the task into the appropriate workpool.
//Parameter(s): an integer called workPoolID which indicates the workpool the task
//				is to be inserted into and an integer called task which is
//				the task to be inserted.
//Precondition(s): N/A
//Return: N/A.
//Side Effect: The task will be put into the appropriate workpool

void *TestFunc(void *id);
//A placeholder function

void Init(sem_t *sem);
//purpose: Initalizes a semaphore
//Parameter(s): a sem_t pointer that is the semaphore to be initalized
//Precondition(s): N/A
//Return: N/A.
//Side Effect: The semaphore will be initalized 

void Destroy(sem_t *sem);
//purpose: Destroys a semaphore
//Parameter(s): a sem_t pointer that is the semaphore to be destroyed
//Precondition(s): The semaphore has been initalized
//Return: N/A.
//Side Effect: The semaphore will be destroyed 

void Lock(sem_t *sem);
//purpose: Locks a semaphore
//Parameter(s): a sem_t pointer that is the semaphore to be locked
//Precondition(s): The semaphore has been initialized 
//Return: N/A.
//Side Effect: The semaphore will be locked

void Unlock(sem_t *sem);
//purpose: Unlocks a semaphore
//Parameter(s): a sem_t pointer that is the semaphore to be locked
//Precondition(s): The semaphore has been initalized 
//Return: N/A.
//Side Effect: The semaphore will be Unlocked

#endif