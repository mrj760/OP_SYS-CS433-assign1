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
    switch (listcount)
    {
        case(0): // adding first element to the list
            first = new Node(proc);
            listcount = 1;
            break;
        case(1): // only first element exists in list
            last = new Node(proc);
            first->next = last;
            listcount = 2;
            break;
        default: // multiple elements already exist in the list
            last->next = new Node(proc);
            last = last->next;
            ++listcount;
            break;
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
    // nothing necessary here
}

// iterate through all nodes in non-empty lists and delete
ReadyQueue::~ReadyQueue()
{
    for (int i = 0; i < MAXP; ++i)
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

// returns either the original PID if it is unique or a new one if not
int ReadyQueue::unique(const int& pid)
{
    if (!pids[pid-1])
        return pid;
    for (int i = 0; i < MAXID; ++i)
    {
        if (!pids[i])
        {
            return i+1;
        }
    }
    return -1;
}

// add a process to the queue by finding the right priority list to add it to
void ReadyQueue::addPCB(PCB* proc)
{
    // cout << "Adding: {" << proc << "}" << endl;
    int p = proc->priority-1;
    int unq = unique(proc->id);
    if (unq == -1)
    {   
        return; // no unique IDs available, do not add
    }
    else
        proc->id = unq;
    if (p < highestPriority)
        highestPriority = p;
    proc->state = ProcState::READY;
    Q[p].addRear(proc);
    pids[unq-1] = 1;
    ++count;
}

// remove the highest priority job
PCB* ReadyQueue::removePCB()
{
    if (count < 1)
        return nullptr;
    for (int i = highestPriority; i < MAXP; i++)
    {
        if (Q[i].listcount < 1)
            continue;

        PCB* ret = Q[i].removeFront();
        ret->state = ProcState::RUNNING;
        // cout << "Removed: {" << ret << "}" << endl;
        --count;
        highestPriority = (Q[i].listcount > 0) ? highestPriority : highestPriority+1;
        pids[ret->id-1] = 0;
        return ret;
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
    for (int i = 0; i < MAXP; ++i)
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