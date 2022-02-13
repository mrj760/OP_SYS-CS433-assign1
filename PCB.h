#pragma once
#include <iostream>
using namespace std;

// Remember to add comments to your code
// ...

// enum class of process state
// A process (PCB) in ready queue should be in READY state
enum class ProcState {NEW, READY, RUNNING, WAITING, TERMINATED};

/* 
Process control block(PCB) is a data structure representing a process in the system.
A process should have at least an ID and a state(i.e.NEW, READY, RUNNING, WAITING or TERMINATED).
It may also have other attributes, such as scheduling information (e.g. priority)
*/
class PCB {
public:
	unsigned int id; // The unique process ID
	unsigned int priority; // The priority of a process valued between 1-50. Larger number represents higher priority
	ProcState state; // The current state of the process. (A process in the ReadyQueue should be in READY state)

	PCB(const int); // Constructor takes only ID. Priority is default (same as ID). State is default (ready)
	PCB(const int, unsigned const int); // Constructor takes ID and priority. State is default (ready)
	PCB(const int, const ProcState); // Constructor takes ID and state. Priority is default (same as ID)
	PCB(const int, unsigned const int, const ProcState); // Constructor taking ID, priority, and state

	bool operator>(const PCB& other); // returns true if the priority of the first process is greater than that of the second process
	bool operator<(const PCB& other); // returns true if the priority of the first process is less than that of the second process
	bool operator==(const PCB& other); // returns true if the priority of the first process equals that of the second process
	friend ostream& operator<<(ostream& os, const PCB& p); // Sends a text summary of the process to an ostream
};

