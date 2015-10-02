#include <string>
#include <iostream>
using namespace std;

const int HEAP_SIZE = 16;
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

class PQ
{
private:
	int jobID;
    int elementCount;
    Job a[HEAP_SIZE];

public:
	enum PriorityChange { INCREASE, DECREASE };

	PQ();
    void BuildHeap();

	void List();
	void Add(Job);
	void Remove(int);
	Job ReleaseNext();
	void ChangePriority(int, int);
};