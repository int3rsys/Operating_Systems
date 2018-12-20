#ifndef _QUEUEL_H
#define _QUEUEL_H
#include "Headers.hpp"

// Single Producer - Multiple Consumer queue
template <typename T>class PCQueue
{

public:

	PCQueue(){
	    q = std::queue<T>();
        pthread_mutex_init(&main_lock,NULL);
        pthread_cond_init(&producer_finished,NULL);
        is_producer_inside = 0;
        //q_size = 0;
    }

    ~PCQueue(){
	    pthread_mutex_destroy(&main_lock);
        pthread_cond_destroy(&producer_finished);
    }

	// Blocks while queue is empty. When queue holds items, allows for a single
	// thread to enter and remove an item from the front of the queue and return it. 
	// Assumes multiple consumers.
	T pop(){
        pthread_mutex_lock(&main_lock);

        while(q.empty() || is_producer_inside ){
            pthread_cond_wait(&producer_finished, &main_lock);
        }
        T res = q.front();
        q.pop();
        //q_size--;
        pthread_mutex_unlock(&main_lock);

        return res;
	}

	// Allows for producer to enter with *minimal delay* and push items to back of the queue.
	// Hint for *minimal delay* - Allow the consumers to delay the producer as little as possible.  
	// Assumes single producer 
	void push(const T& item){

        is_producer_inside = 1;
        pthread_mutex_lock(&main_lock);

        q.push(item);
        //q_size++;
        is_producer_inside = 0;

        pthread_cond_broadcast(&producer_finished);

        pthread_mutex_unlock(&main_lock);
	}

    bool is_empty(){
	    //Need to lock?
	    bool res = q.empty();
        return res;
	}
private:
	// Add your class members here
	pthread_mutex_t main_lock;

	pthread_cond_t producer_finished;
	int is_producer_inside;
    //int q_size;
	std::queue<T> q;

};
// Recommendation: Use the implementation of the std::queue for this exercise
#endif