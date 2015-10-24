#ifndef PriorityQueue_h
#define PriorityQueue_h

#include <iostream>
using namespace std;
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
    bool Find(string item, char& code) const;
private:
    void Find(int i, string item, char& code, bool& found) const;
};

#endif /* PriorityQueue_h */
