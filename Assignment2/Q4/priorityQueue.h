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

struct PrintQueue
{
	int elementCount;
	Job a[HEAP_SIZE];
};

class PQ
{
private:
	PrintQueue queue;
	int jobID;

public:
	enum PriorityChange { INCREASE, DECREASE };

	PQ();

	void List();
	void Add(Job);
	void Remove();
	void ReleaseNext();
	void ChangePriority(Job, PriorityChange);
};