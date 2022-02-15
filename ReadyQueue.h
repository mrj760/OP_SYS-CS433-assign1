// Remember to add comments to your code
// ...

#pragma once

#include "PCB.h"

/* List of processes with a certain priority. Only ever need to add to the rear or delete from the front */


/**
 * ReadyQueue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue here uch that the process with the highest priority
 * can be selected next.
 */
class ReadyQueue {
public:
	// TODO: Implement the required functions. Add necessary member fields and functions
	// You may use different parameter signatures from the example below
	// add a PCB representing a process into the ready queue.
	ReadyQueue();
	~ReadyQueue();

	void addPCB(PCB*);

	// remove and return the PCB with the highest priority from the queue
	PCB* removePCB();

	void display();	 // display all jobs

	// Returns the number of elements in the queue.
	int size();
	
	const static int MAX = 49; // jobs hashed by priority, which can only be up to 50

private:
	struct Node // contains a job and a pointer to the next job of the same priority
	{
		PCB* process;
		Node* next;

		Node(PCB*);
	};
	class List // contains jobs of the same priority
	{
		private:
		Node* first = nullptr;
		Node* last = nullptr;
		unsigned int listcount = 0;

		void addRear(PCB*);
		PCB* removeFront();

		friend ReadyQueue;
	};
	int count = 0;
	List Q[MAX]; // array holding lists of jobs
};
