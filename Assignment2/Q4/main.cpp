#include "priorityQueue.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
	PQ printQueue;

	int cmd;
	Job toAdd;
	while (1)
	{
		cout << "What do you want to do? ";
		cin >> cmd;

		switch (cmd)
		{
		case 1:
			printQueue.List();
			break;
		case 2:
			cout << "Filename: ";
			cin >> toAdd.filename;
			cout << "File Size: ";
			cin >> toAdd.fileSize;
			cout << "Priority: ";
			cin >> toAdd.priority;
			printQueue.Add(toAdd);
			printQueue.List();
			break;
		case 3:
			printQueue.Remove();
			break;
		case 4:
			printQueue.ReleaseNext();
			break;
		case 5:
			//printQueue.ChangePriority();
			break;
		case 0:
			return 0;
		};
	}
	return 0;
}