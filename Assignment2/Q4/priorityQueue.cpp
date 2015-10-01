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
        Job temp = a[i]; // Copy parent
        while (i * 2 <= elementCount) // Loop through each child
        {
            int child = i * 2;
            // Compare children, check if right child is smaller than left child
            if (child != elementCount && (a[child + 1].priority < a[child].priority ||
                (a[child + 1].priority == a[child].priority && a[child + 1].fileSize < a[child].fileSize)))
            {
                child++;
            }
            // Compare parent and child priority
            if (a[child].priority < temp.priority)
            {
                a[i] = a[child];
            }
            // If priority the same, compare parent and child filesize.
            else if (a[child].priority == temp.priority && a[child].fileSize < temp.fileSize)
            {
                a[i] = a[child];
            }
            else break;
            i = child;
        }
        a[i] = temp; // Copy parent to location it satisfies heap order property
        j--;
        i = j;
    }
    
}

void PQ::List()
{
    int originalCount = elementCount;
    
    // Delete min and place value back into array without incrementing element size
	while (elementCount > 0)
	{
        Job temp = ReleaseNext();
        temp.Print();
        a[elementCount+1] = temp;
	}
    
    // Rebuild heap using original count and array values
    elementCount = originalCount;
    BuildHeap();
}

void PQ::Add(Job toAdd)
{
	toAdd.jobNo = jobID++;
	elementCount++;
	int i = elementCount;
    
    // Check if parent is lower priority, swap if so
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
    // Find job to delete, swap it and last value and decrement count
    for (int i = 1; i < elementCount; i++)
    {
        if (a[i].jobNo == jobID)
        {
            a[i] = a[elementCount];
            elementCount--;
            break;
        }
    }
    // Rebuild
    BuildHeap();
}

Job PQ::ReleaseNext()
{
    // Swap root and last nodes, decrement count
    Job toRet = a[1];
    a[1] = a[elementCount];
    elementCount--;
    
    // Rebuild
    BuildHeap();
    return toRet;
}

void PQ::ChangePriority(int jobID, int newPriority)
{
    // Find job to edit, change priority
    for (int i = 1; i < elementCount; i++)
    {
        if (a[i].jobNo == jobID)
        {
            a[i].priority = newPriority;
            break;
        }
    }
    // Rebuild
    BuildHeap();
}