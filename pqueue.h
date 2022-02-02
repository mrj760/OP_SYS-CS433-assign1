#pragma once

#include <iostream>
#include "PCB.h"
using namespace std;

int const MAX = 11;

class pqueue
{
private:
	PCB Q[MAX]; // array holding jobs - only priority numbers are stored
	int count;	// how many jobs are in the array
				// jobs are in slots 0 through count-1

	// Utility functions
	void swap(const int&, const int&);
	void reheapify(); // reheapify after printing
		// - involves moving the last job to the front and trickling down
	int getSmallerchild(const int&); // return location of the smaller child
							  //- compares L and R children of the given location
	void trickleup();		  // trickling up after adding at the rear
	int getParent(const int&);		  // return the parent location given the child loc
	bool even(const int&);			  // is the number even?  Needed to find the parent
    
public:
	pqueue();
	~pqueue();
	void insertjob(PCB* job); // supply the job priority number
    void printjob();
	void displayAll();	 // display all jobs
};
