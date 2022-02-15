#include <iostream>
#include "ReadyQueueHeap.h"

// TODO: Add your implementation of ReadyQueue functions here

// constructor
ReadyQueueHeap::ReadyQueueHeap()
{
	count = 0; // no jobs yet
}

// destructor
ReadyQueueHeap::~ReadyQueueHeap() 
{
    for (int i = 0; i < MAX; i++)
    {
        delete Q[i];
    }
}

// Purpose: to add a job to a right place in the ReadyQueue
// Arguments: 
void ReadyQueueHeap::addPCB(PCB* p)
{
	// cout << "Adding: " << p << endl;
	if (count >= MAX)
	{
		// cout << "...cannot add.. full." << endl;
		return;
	}
	//  add the job j at the rear (and update count)
	//    if impossible else display error message.
	p->state = ProcState::READY;
	Q[count++] = p;
	trickleup(); // moves the job to the right place
}

int ReadyQueueHeap::size()
{
	return count;
}

// Purpose: to print a job and reheapify the ReadyQueue
PCB* ReadyQueueHeap::removePCB()
{
	if (count < 1)
	{
		// cout << "ReadyQueue is empty. No PCB to remove." << endl;
		return nullptr;
	}
	PCB* ret = Q[0];
	ret->state = ProcState::RUNNING;
	reheapify();
	// cout << "Removed: " << ret << endl;
	return ret;
}

// Purpose: to display all jobs
void ReadyQueueHeap::display()
{
	cout << "Jobs:" << count << "\n\t";
	// loop to display jobs from slot 0 to slot count-1 horizontally.
	//  No need to show a tree format.
	int i = 0;
	while (i < count)
		cout << Q[i++] << "\n\t";
	cout << endl;
}

//  swap values in locations loc1 and loc2
void ReadyQueueHeap::swap(const int& loc1, const int& loc2)
{
	PCB* temp = Q[loc1];
	Q[loc1] = Q[loc2];
	Q[loc2] = temp;
}

// Purpose: to make very last job trickle up to right location.
void ReadyQueueHeap::trickleup()
{
	int x = count - 1; // very last job's location
	//  While x is > 0 :
	//  	compare Q[x] with parent value.
	//	    if parent value is bigger, call swap & update x to be parent location. 
	//		Otherwise stop loop.
	//    	Call getParent to get location of parent based on child's location.
	while (x > 0)
	{
		int p = getParent(x);
		if (*Q[x] < *Q[p])
		{
			swap(x, p);
			x = p;
		}
		else
			break;
	}
}

// Find location of parent based on child location
int ReadyQueueHeap::getParent(const int& childloc)
{
	return even(childloc) ? (childloc - 2) / 2 : (childloc - 1) / 2;
}

// even/odd important for getParent location
bool ReadyQueueHeap::even(const int& i)
{
	return i % 2 == 0;
}

// Reheapify ReadyQueue by trickling down
void ReadyQueueHeap::reheapify()
{
	
	Q[0] = Q[count - 1]; // move the last job to the front
	count--;

	/*  Start X at 0 (the root)
	 	While X is within array (the used portion):
	    	Find location of smaller child by calling getSmallerchild.
	    	(if location of both children are off-tree, stop loop).
	    	If smaller child is smaller than parent value,
			call swap and X becomes smaller child's location.
	    	else no swaps so stop loop. */

    int x = 0;			 // current location
	while (x < (count - 1))
	{
		int sc = getSmallerchild(x); // sc: "smaller child"
		if (sc == -1 || *Q[x] < *Q[sc])
			return; // both children off-tree, or parent is smaller than smallest child
		swap(x, sc);
		x = sc;
	}
}

// Find location of smaller child
// Children are at locations 2*i+1 and 2*i+2
int ReadyQueueHeap::getSmallerchild(const int& i)
{
	int LC = 2 * i + 1,
        RC = 2 * i + 2; // locations of children (LC: Left child, RC: Right child)

	// One or both of them may be beyond count-1 or just the RC is beyond count-1
	if (RC > count - 1)
	{
		if (LC > count - 1) // If both are beyond count-1
			return -1;
		return LC; // LC is within bounds but RC is not.
	}

	return *Q[LC] < *Q[RC] ? LC : RC; // return location of smaller child
}
