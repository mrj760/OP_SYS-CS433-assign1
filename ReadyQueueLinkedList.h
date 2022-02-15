// Remember to add comments to your code
// ...

#pragma once
#include "PCB.h"

/**
 * ReadyQueue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue here uch that the process with the highest priority
 * can be selected next.
 */
class ReadyQueueLinkedList {
public:
	// TODO: Implement the required functions. Add necessary member fields and functions
	// You may use different parameter signatures from the example below
	// add a PCB representing a process into the ready queue.
	ReadyQueueLinkedList();
	~ReadyQueueLinkedList();

	void addPCB(PCB*);

	// remove and return the PCB with the highest priority from the queue
	PCB* removePCB();

	void display();	 // display all jobs

	int size(); // Returns the number of elements in the queue.
	
	const static int MAX = 50, MIN = 1; // Maximum/Minimum priorities

private:
	struct Node // contains a job and a pointer to the next node holding a lower priority job
	{
		PCB* proc;
		Node* next;

		Node(PCB*);
		Node();
	};
    Node* first;
	Node* last;
	int count;
};
