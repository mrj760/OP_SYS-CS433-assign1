// Remember to add comments to your code

#include <iostream>
#include <cstdlib>
#ifdef __linux__
#include <sys/time.h>
#endif
#ifdef _WIN32
// #include <time.h>
#include <chrono>
#endif
#include "ReadyQueue.h"

int main(int argc, char* argv[]) {
	//Print basic information about the program
	std::cout << "CS 433 Programming assignment 1" << std::endl;
	std::cout << "Author: Christian Contreras, Micah Johnson and Eric Tyler" << std::endl;
	std::cout << "Date: 02/15/2022" << std::endl;
	std::cout << "Course: CS433 (Operating Systems)" << std::endl;
	std::cout << "Description : Program to implement a priority ready queue of processes" << std::endl;
	std::cout << "=================================" << std::endl;

	// TODO: Add your code for Test 1
	std::cout << "Performing Test 1" << std::endl;
	//TODO: add processes 14, 1, 28, 39 and 18 to q1. Display the content of q1
	ReadyQueue q1;
	q1.addPCB(new PCB(14));
	q1.addPCB(new PCB(1));
	q1.addPCB(new PCB(28));
	q1.addPCB(new PCB(39));
	q1.addPCB(new PCB(18));
	q1.display();
	//TODO: remove one process with the highest priority from q1 and display q1.
	q1.removePCB();
	q1.display();
	//TODO: add additional processes 48, 10, 31 and 19 into q1, and display q1.
	q1.addPCB(new PCB(48));
	q1.addPCB(new PCB(10));
	q1.addPCB(new PCB(31));
	q1.addPCB(new PCB(19));
	q1.display();
	//TODO: remove one process with the highest priority from q1 and display q1.
	q1.removePCB();
	q1.display();
	//TODO: add additional processes 29, 41, 18 and 46 to q1 and display q1.
	q1.addPCB(new PCB(10));
	q1.addPCB(new PCB(10));
	q1.addPCB(new PCB(10));
	q1.addPCB(new PCB(46));
	q1.display();
	//TODO: One by one remove the process with the highest priority from the queue q1 and display the queue after each removal.
	while (q1.size() > 0)
	{
		q1.removePCB();
		q1.display();
	}

	// TODO: Add your code for Test 2
	std::cout << "Performing Test 2" << std::endl;
	//start timer 
	
	#ifdef _WIN32
	auto start = std::chrono::high_resolution_clock::now();
	#endif

	#ifdef __linux__
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
    #endif

	ReadyQueue q2;
    for (int i = 0; i < 1000000; i++) {
       	//TODO: add or remove a process with equal probabilty
		
	}

	// end timer
	#ifdef __linux__
	clock_gettime(CLOCK_MONOTONIC, &end);
	//Calculating total time taken by the program.
    double time_taken = (end.tv_sec + end.tv_nsec*1e-9) - (start.tv_sec + start.tv_nsec*1e-9);
	printf("Test 2 run time = %f seconds\n", time_taken);
	#endif

	#ifdef _WIN32
	auto end  = std::chrono::high_resolution_clock::now();
	auto elapsed = end - start;
	printf("Test 2 run time = %f seconds\n", elapsed);
	#endif

	return 0;
}
