#include "priorityQueue.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
	PQ printQueue;

	char cmd;
	Job toAdd;
    int jobID;
    int newPriority;
	while (1)
	{
		cout << "What do you want to do? ";
		cin >> cmd;

		switch (cmd)
		{
            case '1':
                printQueue.List();
                break;
            case '2':
                cout << "Filename: ";
                cin >> toAdd.filename;
                cout << "File Size: ";
                cin >> toAdd.fileSize;
                while (1)
                {
                    cout << "Priority: ";
                    cin >> toAdd.priority;
                    if (toAdd.priority <= 0 || toAdd.priority > 3)
                    {
                        cout << "Invalid.  Must be 1-3" << endl;
                    }
                    else break;
                }
                printQueue.Add(toAdd);
                break;
            case '3':
                cout << "What job do you want to remove? ";
                cin >> jobID;
                printQueue.Remove(jobID);
                break;
            case '4':
                printQueue.ReleaseNext();
                break;
            case '5':
                cout << "What job do you want to edit? ";
                cin >> jobID;
                while (1)
                {
                    cout << "What is the new priority? ";
                    cin >> newPriority;
                    if (newPriority <= 0 || newPriority > 3)
                    {
                        cout << "Invalid.  Must be 1-3" << endl;
                    }
                    else break;
                }
                printQueue.ChangePriority(jobID, newPriority);
                break;
            case 'q':
            case 'Q':
                return 0;
            default:
                cout << "Invalid command.  Valid commands are:\n";
                cout << "1 - List\n";
                cout << "2 - Add\n";
                cout << "3 - Delete Job\n";
                cout << "4 - Remove Next\n";
                cout << "5 - Change Job Priority\n";
                cout << "q - Exit\n";
                break;
		};
	}
	return 0;
}