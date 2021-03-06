// Remember to add comments to your code
// ...

#pragma once

#include "PCB.h"

/**
 * ReadyQueue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue here uch that the process with the highest priority
 * can be selected next.
 */
class ReadyQueueHeap {
public:
	// TODO: Implement the required functions. Add necessary member fields and functions
	// You may use different parameter signatures from the example below
	// add a PCB representing a process into the ready queue.

	ReadyQueueHeap();
	~ReadyQueueHeap();

	void addPCB(PCB*);

	// remove and return the PCB with the highest priority from the queue
	PCB* removePCB();

	void display();	 // display all jobs

	// Returns the number of elements in the queue.
	int size();

	// move the last job to the front and trickle down (removes lowest priority job)
	void reheapify(); 

private:
	const static int MAX = 49; // jobs hashed by priority, which can only be up to 50
	int count = 0;
	PCB* Q[MAX]; // array holding lists of jobs

	// Prints the queue contents to standard output.
	void swap(const int&, const int&);

	// return location of the smaller child - compares L and R children of the given location
	int getSmallerchild(const int&); 

	// trickling up after adding at the rear
	void trickleup();		  

	// return the parent location given the child loc
	int getParent(const int&);	

	// is the number even?  Needed to find the parent	  
	bool even(const int&);
};
