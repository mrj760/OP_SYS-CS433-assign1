#include "PCB.h"


// TODO: Add your implementation here
PCB::PCB()
{
    this->id = 0;
    this->priority = 0;
    this->state = ProcState::READY;
}

PCB::PCB(const int id)
{
    this->id = id;
    this->priority = id;
    this->state = ProcState::READY;
}

PCB::PCB(const int id, unsigned const int priority)
{
    this->id = id;
    this->priority = priority;
    this->state = ProcState::READY;
}

PCB::PCB(const int id, unsigned const int priority, const ProcState state)
{
    this->id = id;
    this->priority = priority;
    this->state = state;
}

bool PCB::operator>(const PCB& other)
	{
		return priority > other.priority;
	}

bool PCB::operator<(const PCB& other)
	{
		return priority < other.priority;
	}

ostream& operator<<(ostream& os, const PCB& p)
{
		os << "ID: " << p.id << ", Priority: " << p.priority << ", State: ";
		switch (p.state)
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