#ifndef PriorityQueue_h
#define PriorityQueue_h

#include <stdio.h>
#include "Elements.h"

class PriorityQueue
{
private:
    int elementCount;
    int MAX_SIZE;
    PCTreeNode* a;
public:
	PriorityQueue(int maxSize);
	~PriorityQueue();
	void BuildHeap();
	void BuildFromArray(PCTreeNode arr[], int size);
	PCTreeNode DeleteMin();
	int GetSize() const;
	void Insert(PCTreeNode t);
	void Insert(PCTreeNode* t);
};

#endif /* PriorityQueue_h */
