#include "ReadyQueue.h"

// Creates a node with a job that doesn't point to anything yet
ReadyQueue::Node::Node(PCB* proc)
{
    process = proc;
    next = nullptr;
}

// adds a node with the given job at the end of the list of a certain priority
void ReadyQueue::List::addRear(PCB* proc)
{
    if (listcount > 1) // elements already exist in the list
    {
        last->next = new Node(proc);
        last = last->next;
        ++listcount;
    }
    else if (listcount < 1) // adding first element to the list
    {
        first = new Node(proc);
        listcount = 1;
        
    }
    else // only first element exists in list
    {
        last = new Node(proc);
        first->next = last;
        listcount = 2;
    }
}

// remove the first job in the list
PCB* ReadyQueue::List::removeFront()
{
    PCB* ret = first->process;
    Node* del = first;
    first = first->next;
    
    delete del;
    --listcount;
    return ret;
}

ReadyQueue::ReadyQueue()
{

}

// iterate through all nodes in non-empty lists and delete
ReadyQueue::~ReadyQueue()
{
    for (int i = 0; i < MAX; ++i)
    {
        if (Q[i].listcount > 0)
        {
            Node* cur = Q[0].first;
            while (cur != nullptr)
            {
                Node* del = cur;
                cur = cur->next;
                delete del;
            }
        }
    }
}

// add a process to the queue by finding the right priority list to add it to
void ReadyQueue::addPCB(PCB* proc)
{
    // cout << "Adding: {" << proc << "}" << endl;
    proc->state = ProcState::READY;
    int slot = proc->priority-1;
    Q[slot].addRear(proc);
    ++count;
}

// remove the highest priority job
PCB* ReadyQueue::removePCB()
{
    if (count < 1)
        return nullptr;
    for (int i = 0; i < MAX; i++)
    {
        if (Q[i].listcount > 0)
        {
            PCB* ret = Q[i].removeFront();
            ret->state = ProcState::RUNNING;
            // cout << "Removed: {" << ret << "}" << endl;
            --count;
            return ret;
        }
    }
    return nullptr; // doesn't do anything, just here for compiler sanity
}

// display all jobs sorted/grouped by their priorities
void ReadyQueue::display()
{
    if (count < 1)
    {
        cout << "~~~~~~~~~~~\nReadyQueue is empty!\n~~~~~~~~~~~\n";
        return;
    }

    cout << "~~~~~~~~~~~\nReadyQueue Summary:\n~~~~~~~~~~~\n";
    for (int i = 0; i < MAX; ++i)
    {
        if (Q[i].listcount > 0)
        {
            cout << "Processes with Priority (" << i+1 << ") :";
            Node* cur = Q[i].first;
            int processesPerLine = 4;
            int lineCount = 0;
            while (cur != nullptr)
            {
                cout << "{" << (cur->process) << "}  ";
                if (++lineCount % processesPerLine == 0 && cur->next != nullptr)
                    cout << "\n\t\t\t\t";
                cur = cur->next;
            }
            cout << endl;
        }
    }
    cout << "~~~~~~~~~~~\nEND ReadyQueue Summary.\n~~~~~~~~~~~\n";
}

// return the number of jobs in the queue
int ReadyQueue::size()
{
    return count;
}