#include <iostream>
#include "priorityQueue.h"
using namespace std;


PQ::PQ()
{
	elementCount = 0;
	jobID = 1;
	for (int i = 0; i < HEAP_SIZE; i++)
	{
		a[i].filename = "";
		a[i].fileSize = 0;
		a[i].priority = 0;
		a[i].jobNo = 0;
	}
}

void PQ::BuildHeap()
{
    if (elementCount < 1) return;
    
    int j = elementCount / 2;
    int i = j;
    while (i > 0)
    {
        Job temp = a[i];
        while (i * 2 <= elementCount)
        {
            int child = i * 2;
            if (child != elementCount && (a[child + 1].priority < a[child].priority ||
                (a[child + 1].priority == a[child].priority && a[child + 1].fileSize < a[child].fileSize)))
            {
                child++;
            }
            if (a[child].priority < temp.priority)
            {
                a[i] = a[child];
            }
            else if (a[child].priority == temp.priority && a[child].fileSize < temp.fileSize)
            {
                a[i] = a[child];
            }
            else break;
            i = child;
        }
        a[i] = temp;
        j--;
        i = j;
    }
    
}

void PQ::List()
{
    int originalCount = elementCount;
	while (elementCount > 0)
	{
        Job temp = ReleaseNext();
        temp.Print();
        a[elementCount+1] = temp;
	}
    elementCount = originalCount;
    BuildHeap();
}

void PQ::Add(Job toAdd)
{
	toAdd.jobNo = jobID++;
	elementCount++;
	int i = elementCount;
	while (i > 1 && (toAdd.priority < a[i / 2].priority ||
                    (toAdd.priority == a[i / 2].priority && toAdd.fileSize < a[i / 2].fileSize)))
	{
		a[i] = a[i / 2];
		i = i / 2;
	}
	a[i] = toAdd;
}

void PQ::Remove(int jobID)
{
    for (int i = 1; i < elementCount; i++)
    {
        if (a[i].jobNo == jobID)
        {
            a[i] = a[elementCount];
            elementCount--;
            break;
        }
    }
    BuildHeap();
}

Job PQ::ReleaseNext()
{
    Job toRet = a[1];
    a[1] = a[elementCount];
    elementCount--;
    
    BuildHeap();
    return toRet;
}

void PQ::ChangePriority(int jobID, int newPriority)
{
    for (int i = 1; i < elementCount; i++)
    {
        if (a[i].jobNo == jobID)
        {
            a[i].priority = newPriority;
            break;
        }
    }
    BuildHeap();
}