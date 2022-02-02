#include "pqueue.h"

// constructor
pqueue::pqueue()
{
	count = 0; // no jobs yet
}

// destructor
pqueue::~pqueue() {}

// Purpose: to add a job to a right place in the Pqueue
// Arguments: 
void pqueue::insertjob(PCB* p)
{
	cout << "Adding: " << *p << endl;
	if (count >= MAX)
	{
		cout << "...cannot add.. full." << endl;
		return;
	}
	//  add the job j at the rear (and update count)
	//    if impossible else display error message.
	Q[count++] = *p;
	trickleup(); // moves the job to the right place
}

// Purpose: to print a job and reheapify the Pqueue
void pqueue::printjob()
{
	cout << "Printing: " << Q[0] << endl;
	reheapify();
}

// Purpose: to display all jobs
void pqueue::displayAll()
{
	cout << "Jobs: ";
	// loop to display jobs from slot 0 to slot count-1 horizontally.
	//  No need to show a tree format.
	int i = 0;
	while (i < count)
		cout << Q[i++] << " ";
	cout << endl;
}

// Utility functions follow: ------------------

//  swap values in locations loc1 and loc2
void pqueue::swap(const int& loc1, const int& loc2)
{
	PCB temp = Q[loc1];
	Q[loc1] = Q[loc2];
	Q[loc2] = temp;
}

// Purpose: to make the very last job trickle up to the right location.
void pqueue::trickleup()
{
	int x = count - 1; // the very last job's location
	//  While x is > 0
	//    compare Q[x] with the parent value (*)
	//    and if the parent value is bigger call swap & update x
	//    to be the parent location. Otherwise stop the loop.
	// (*) Call getParent to get the location of the parent
	//            based on the child's location.
	while (x > 0)
	{
		int p = getParent(x);
		if (Q[x] < Q[p])
		{
			swap(x, p);
			x = p;
		}
		else
			break;
	}
}

// Purpose: find the location of the parent
// The child location is given.  Need to call even.
int pqueue::getParent(const int& childloc)
{
	return even(childloc) ? (childloc - 2) / 2 : (childloc - 1) / 2; //  return the parent location based on the child loc
}

// even/odd important for finding parent location
bool pqueue::even(const int& i)
{
	return i % 2 == 0;
}

// Purpose: to reheapify the Pqueue by trickling down
void pqueue::reheapify()
{
	
	Q[0] = Q[count - 1]; // move the last job to the front
	count--;

	/*  Start X at 0 (the root)
	 	While X is within the array (the used portion):
	    	Find the location of the smaller child by calling getSmallerchild.
	    	(if the location of both children are off the tree, stop the loop).
	    	If the smaller child is smaller than the parent value,
			call swap and X becomes the smaller child's location.
	    	else no swaps so stop to loop. */

    int x = 0;			 // the current location
	while (x < (count - 1))
	{
		int sc = getSmallerchild(x); // sc: "smaller child"
		if (sc == -1 || Q[x] < Q[sc])
			return; // both children off tree, or parent is smaller than smallest child
		swap(x, sc);
		x = sc;
	}
}

// Purpose: to find the location of the smaller child
// where children are at locations 2*i+1 and 2*i+2
int pqueue::getSmallerchild(const int& i)
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

	return Q[LC] < Q[RC] ? LC : RC; // return the location of the smaller child
}
// NEVER GO TO UNUSED PART OF THE ARRAY
