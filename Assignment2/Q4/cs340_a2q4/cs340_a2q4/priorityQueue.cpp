#include <iostream>
#include "priorityQueue.h"
using namespace std;


PQ::PQ()
{
	queue.elementCount = 0;
	jobID = 1;
	for (int i = 0; i < HEAP_SIZE; i++)
	{
		queue.a[i].filename = "";
		queue.a[i].fileSize = 0;
		queue.a[i].priority = 0;
		queue.a[i].jobNo = 0;
	}
}

void PQ::List()
{
	for (int i = 1; i <= queue.elementCount; i++)
	{
		queue.a[i].Print();
	}
}

void PQ::Add(Job toAdd)
{
	toAdd.jobNo = jobID++;
	queue.elementCount++;
	int i = queue.elementCount;
	while (i > 1 && toAdd.priority < queue.a[i/2].priority)
	{
		queue.a[i] = queue.a[i / 2];
		i = i / 2;
	}
	queue.a[i] = toAdd;
	while (i > 1 && 
		(queue.a[i].priority == queue.a[i / 2].priority && queue.a[i].fileSize < queue.a[i / 2].fileSize))
	{
		Job temp;
		temp = queue.a[i / 2];
		queue.a[i / 2] = queue.a[i];
		queue.a[i] = temp;
		i = i / 2;
	}
}

void PQ::Remove()
{

}

void PQ::ReleaseNext()
{

}

void PQ::ChangePriority(Job j, PriorityChange pc)
{

}