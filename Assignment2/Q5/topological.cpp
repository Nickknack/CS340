#include "topological.h"

using namespace std;


Leader* head;
Leader* tail;
Leader* p;
Leader* q;
Leader* r;
Leader* t;
Follower* f;
string x, y;
int elementCount, i, zeroDegree, zeroCount;

void TopologicalSort(ifstream& input)
{
	//Initializes a new empty Leader node that head points to. 
	//initialize tail to also point to the new head leader (nothing has been added
	//to the list yet).
	//Since nothing has been added, elementCount is 0.
	head = new Leader;
	tail = head;
	elementCount = 0;

	//Read in the first value to x.

	//Read in the values from the input into the list until the end of the file is reached.
	input >> x;
	while (input)
	{	
		//Read in the main prereq into x and the non-prereq into y
		input >> y;

		//put the x and y values into the end of the list.
		p = BuildList(x, head, tail, elementCount);
		q = BuildList(y, head, tail, elementCount);

		//create a new follower node and 
		f = new Follower;

		//Set the adjacentLeader value of the follower to the non-prereq and the 
		//nextFollower to the firstFollower of the prereq.
		f->adjacentLeader = q;
		f->nextFollower = p->firstFollower;

		//set the prereq's firstFollower to the new follower and
		//increment the inDegree's of the non-prereq by 1 (it now is the follower of 1 entry)
		p->firstFollower = f;
		q->inDegree++;

		input >> x;
	}

	//set p to point to head, head to point to NULL, and r to point at tail
	p = head;
	head = NULL;
	r = tail;

	zeroDegree = 0;

	//this loop is creating a list starting with the first entry with indegree 0
	//followed by each other element with inDegree 0. zeroDegree contains the amount of elements
	//with indegree of 0
	while (p != r)
	{
		//set q to point to p and p to point to the next leader of p
		q = p;
		p = p->nextLeader;

		//if the q's inDegree is 0, that means it doesn't have any prereqs
		if (q->inDegree == 0)
		{
			//Set the nextLeader to point to the head and then set the head to q
			q->nextLeader = head;
			head = q;

			//increment zeroDegree; if zeroDegree is 1 that means it was the first value to have 
			//0 inDegrees. Set the tail to point to q.
			zeroDegree++;
			if (zeroDegree == 1)
			{
				tail = q;
			}
		}
	}

	//set q to the head and r to the tail so that the list can be printed. 
	q = head;
	r = tail;

	//Traverse the list, printing out the order.
	while (q != NULL)
	{
		t = q;
		for (i = 0; i < zeroDegree; i++)
		{
			//print the entries that have an indegree of 0; these can be done concurently
			cout << t->element << " ";
			elementCount--;			
			t = t->nextLeader;
		}

		cout << endl;

		//zeroCount is used to count how many new elements have an inDegree of 0 after
		//the followers have been traversed, zeroDegree will be set to this new value.
		zeroCount = 0;

		for (i = 0; i < zeroDegree; i++)
		{
			f = q->firstFollower;

			//If any of the elements with inDegree of 0 have followers, loop thorugh them
			while (f != NULL)
			{
				//set p to point to the adjacent leader of the follower
				//because q is the prereq for that element. Decrement p's 
				//inDegree to account for the fact that we have 'visited'
				//one of it's prereqs.
				p = f->adjacentLeader;
				p->inDegree--;

				//If all of the prereqs have been 'visited' set p's next leader to be
				//Null and r's nextLeader to be p and r to be p. This puts it behind
				//it's prereqs in the order.
				if (p->inDegree == 0)
				{
					zeroCount++;
					p->nextLeader = NULL;
					r->nextLeader = p;
					r = p;

					if (q == NULL)
					{
						q = r;
					}
				}

				//Once a follower has been completed move on to the next follower
				f = f->nextFollower;
			}
			q = q->nextLeader;
		}
		zeroDegree = zeroCount;
	}
	cout << endl;

	//if elementCount wasn't decremented to zero then there was a failure in the 
	//topological sort.
	if(elementCount != 0)
	{
		cout << endl << endl << "ERROR - SET NOT PARTIALLY ORDERED" << endl << endl;
	}
}

Leader* BuildList (string w, Leader* head, Leader*& tail, int& i)
{
	Leader* h;

	//set the tail value to be the new element
	h = head;
	tail->element = w;

	//traverse the leader list until h points at the tail
	while (h->element != w)
	{
		h = h->nextLeader;
	}
	if (h == tail)
	{
		//since the old tail has a value now, we must create a new tail.
		tail = new Leader;
		//increment the element count since we have added an aditional element
		//and initialize the new element's other values. 
		i++;
		h->inDegree = 0;
		h->firstFollower = NULL;
		h->nextLeader = tail;
	}

	//return a pointer to the new element
	return h;
}