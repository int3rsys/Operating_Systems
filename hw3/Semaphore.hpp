#ifndef __SEMAPHORE_H
#define __SEMAPHORE_H
#include "Headers.hpp"

// Synchronization Warm up 
class Semaphore {
public:
	//Semaphore(); // Constructs a new semaphore with a counter of 0
	Semaphore(unsigned val = 0); // Constructs a new semaphore with a counter of val

	~Semaphore();

	void up(); // Mark: 1 Thread has left the critical section
	void down(); // Block until counter >0, and mark - One thread has entered the critical section.

private:
	// TODO
	pthread_mutex_t global_lock;
	pthread_cond_t not_empty;
	int cnt;

};

#endif
