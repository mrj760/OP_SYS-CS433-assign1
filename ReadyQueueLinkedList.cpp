
#include "ReadyQueueLinkedList.h"

/**
 * ReadyQueue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue here uch that the process with the highest priority
 * can be selected next.
 */

ReadyQueueLinkedList::ReadyQueueLinkedList()
{
    first = nullptr;
    last = nullptr;
    count = 0;
}

ReadyQueueLinkedList::~ReadyQueueLinkedList()
{

}

ReadyQueueLinkedList::Node::Node()
{
    proc = nullptr;
    next = nullptr;
}

ReadyQueueLinkedList::Node::Node(PCB* proc)
{
    this->proc = proc;
    next = nullptr;
}

void ReadyQueueLinkedList::addPCB(PCB* proc)
{
    switch(count)
    {
        case(0): // adding first node to queue
            proc->state = ProcState::READY;
            first = new Node(proc);
            // cout << "Added: " << first->proc << endl;
            break;

        case(1): // adding second node to queue
            if (proc->id == first->proc->id)
            {
                return; // cannot add duplicate pid's
            }
            else if (first->proc->priority < proc->priority) 
            // new job has lower priority, put at end of queue
            {
                proc->state = ProcState::READY;
                last = new Node(proc);
                // cout << "Added: " << last->proc << endl;
            }            
            else
            // new job has higher priority, put at beginning of queue
            {
                proc->state = ProcState::READY;
                last = first;
                first = new Node(proc);
                // cout << "Added: " << first->proc << endl;
            }
            first->next = last;
            break;

        default: // adding third or higher node to queue

            
            Node* newnode = new Node(proc);

            if (proc->priority < first->proc->priority)
            {
                newnode->next = first;
                first = newnode;
                // cout << "Added: " << first->proc << endl;
                ++count;
                // cout << "Checking for duplicates." << endl;
                // check the rest of the list to see if we are adding a duplicate
                Node* dupeCheck = first->next;
                for (int i = 1; i < count; ++i)
                {
                    if (dupeCheck->proc->id == proc->id)
                    {
                        // cout << "Duplicate found." << endl;
                        return; // cannot add duplicates
                    }
                    dupeCheck = dupeCheck->next;
                }
                return;
            }

            Node* current = first;

            int p = proc->priority;
            int pid = proc->id;

            int stepcount = 0;

            // loop until we reach a point of lower priority
            while (current->next != nullptr && p > current->next->proc->priority)
            {   
                ++stepcount;
                // cout << "Adding..." << stepcount << " steps in." << endl;
                if (current->proc->id == pid)
                    return; // cannot add duplicate process ID's
                current = current->next;
            }

            // cout << "Checking for duplicates." << endl;
            // check the rest of the list to see if we are adding a duplicate
            Node* dupeCheck = current;
            for (stepcount; stepcount < count; ++stepcount)
            {
                if (dupeCheck->proc->id == pid)
                {
                    // cout << "Duplicate found." << endl;
                    return; // cannot add duplicates
                }
                dupeCheck = dupeCheck->next;
            }

            // the current process node now either has higher or equal priority as the new process (and is unique)
            newnode->next = current->next;
            current->next = newnode;
            newnode->proc->state = ProcState::READY;
            // cout << "Added: " << current->next->proc << endl;
            break;
    }
    ++count;
    // cout << "There are " << count << " nodes." << endl;
}

PCB* ReadyQueueLinkedList::removePCB()
{
    if (count == 0)
        return nullptr;

    PCB* ret = first->proc;

    ret->state = ProcState::RUNNING;

    Node* del;
    switch(count)
    {
        case(1):
            delete first;
            break;
        case(2):
            del = first;
            first = first->next;
            last = nullptr;
            delete del;
            break;
        default:
            del = first;
            first = first->next;
            delete del;
            break;
    }

    // cout << "Removed: " << ret << endl;
    --count;
    return ret;
}

void ReadyQueueLinkedList::display()
{
    if (count == 0)
    {
        cout << "There are no processes." << endl;
        return;
    }
    else if (count == 1)
    {
        cout << "Processes: {" << first->proc << "}\n";
        return;
    }


    Node* current = first;
    cout << "Processes:\n\t";
    for (int i = 1; i <= count; ++i)
    {
        cout << "{" << current->proc << "}, ";
        current = current->next;
        if (i % 4 == 0)
            cout << "\n\t";
    }
    cout << endl;
}

int ReadyQueueLinkedList::size()
{
    return count;
}