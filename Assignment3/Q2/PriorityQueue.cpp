#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(int maxSize)
{
	elementCount = 0;
	MAX_SIZE = maxSize;
	a = new PCTreeNode[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; i++)
	{
		a[i].character = NULL;
		a[i].frequency = 0;
		a[i].code = "";
		a[i].left = NULL;
		a[i].right = NULL;
	}
}

PriorityQueue::~PriorityQueue()
{

}

void PriorityQueue::BuildHeap()
{
	if (elementCount < 1) return;

	int j = elementCount / 2;
	int i = j;
	while (i > 0)
	{
		PCTreeNode temp = a[i]; // Copy parent
		while (i * 2 <= elementCount) // Loop through each child
		{
			int child = i * 2;
			// Compare children, check if right child is smaller than left child
			if (child != elementCount && a[child + 1].frequency < a[child].frequency)
			{
				child++;
			}
			// Compare parent and child priority
			if (a[child].frequency < temp.frequency)
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

void PriorityQueue::BuildFromArray(PCTreeNode arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		a[i+1] = arr[i];
		a[i + 1].code = "";
		a[i + 1].left = NULL;
		a[i + 1].right = NULL;
	}
	elementCount = size;
	BuildHeap();
}

PCTreeNode PriorityQueue::DeleteMin()
{
	// Swap root and last nodes, decrement count
	PCTreeNode toRet = a[1];
	a[1] = a[elementCount];
	elementCount--;
	PCTreeNode temp = a[1]; // Copy parent
	int i = 1;
	while (i * 2 <= elementCount) // Loop through each child
	{
		int child = i * 2;
		// Compare children, check if right child is smaller than left child
		if (child != elementCount && a[child + 1].frequency < a[child].frequency)
		{
			child++;
		}
		// Compare parent and child priority
		if (a[child].frequency < temp.frequency)
		{
			a[i] = a[child];
		}
		else break;
		i = child;
	}
	a[i] = temp; // Copy parent to location it satisfies heap order property
	return toRet;
}

int PriorityQueue::GetSize() const
{
	return elementCount;
}

void PriorityQueue::Insert(PCTreeNode t)
{
	elementCount++;
	int i = elementCount;
	// Check if parent is lower priority, swap if so
	while (i > 1 && t.frequency < a[i / 2].frequency)
	{
		a[i] = a[i / 2];
		i = i / 2;
	}
	a[i] = t;
}

void PriorityQueue::Insert(PCTreeNode* t)
{
	PCTreeNode temp;
	temp.character = t->character;
	temp.code = t->code;
	temp.frequency = t->frequency;
	temp.left = t->left;
	temp.right = t->right;
	Insert(temp);
}

bool PriorityQueue::Find(string item, char& code) const
{
    bool found;
    Find(1, item, code, found);
    return found;
}

void PriorityQueue::Find(int i, string item, char& code, bool& found) const
// Recursively searches tree for item
{
    cout << item << "\t" << item[0] << endl;
    if (item[0] == '0')
    {
        Find(i*2, item.substr(1), code, found);
    }
    else if (item[0] == '1')
    {
        Find((i*2)+1, item.substr(1), code, found);
    }
    else
    {
        found = true;
        code = a[i].character;
        return;
    }
}