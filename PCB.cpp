#include "PCB.h"

// Constructor takes only ID. Priority is default (same as ID). State is default (new)
PCB::PCB(const int id)
{
    this->id = id;
    this->priority = id;
    this->state = ProcState::NEW;
}

// Constructor takes ID and priority. State is default (new)
PCB::PCB(const int id, unsigned const int priority)
{
    this->id = id;
    this->priority = priority;
    this->state = ProcState::NEW;
}

// Constructor takes ID and state. Priority is default (same as ID)
PCB::PCB(const int id, const ProcState state)
{
    this->id = id;
    this->priority = id;
    this->state = state;
}

// Constructor taking ID, priority, and state
PCB::PCB(const int id, unsigned const int priority, const ProcState state)
{
    this->id = id;
    this->priority = priority;
    this->state = state;
}

// Sends a text summary of the process to an ostream
ostream& operator<<(ostream& os, const PCB* p)
{
		os << "ID: " << p->id << ", Priority: " << p->priority << ", State: ";
		switch (p->state)
		{
			case(ProcState::NEW):
				os << "NEW";
				break;
			case(ProcState::READY):
				os << "READY";
				break;
			case(ProcState::RUNNING):
				os << "RUNNING";
				break;
			case(ProcState::WAITING):
				os << "WAITING";
				break;
			case(ProcState::TERMINATED):
				os << "TERMINATED";
				break;
			default:
				os << "????";
				break;
		}
		return os;
	}