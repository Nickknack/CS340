//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: September 28th, 2015
//Last Modified: September 30th, 2015
//Purpose: Functions and structures for working with a priority queue
//***************************************************************************

#include <string>
#include <iostream>
using namespace std;

// Heap max size (as given in question)
const int HEAP_SIZE = 16;

// Job structure
struct Job
{
	int priority;
	int jobNo;
	string filename;
	int fileSize;

	void Print()
	{
		cout << jobNo << ": " << filename << " " << fileSize << " " << priority << endl;
	}
};

// Priority Queue
class PQ
{
private:
	int jobID; // Counts jobs since creation.
    int elementCount;
    Job a[HEAP_SIZE];

public:
	PQ();
    
    // Builds the heap to satisfy the min heap order property on priority and file size
    void BuildHeap();

    // Lists the jobs in order they will be printed
	void List();
    
    // Add new job to end of heap and percolate up
	void Add(Job);
    
    // Delete specified job and rebuild heap
	void Remove(int);
    
    // Delete min, rebuild heap
	Job ReleaseNext();
    
    // Change priority for selected job, rebuild heap
	void ChangePriority(int, int);
};