#ifndef _QUEUEL_H
#define _QUEUEL_H
#include "Headers.hpp"

// Single Producer - Multiple Consumer queue
template <typename T>class PCQueue
{

public:

	PCQueue(){
	    q = std::queue<T>();
        pthread_mutex_init(&loby_lock,NULL);
        pthread_mutex_init(&vip_lock,NULL);
        pthread_cond_init(&producer_finished,NULL);
        pthread_cond_init(&not_empty,NULL);
        is_producer_waiting = 0;
        producers_count = 0;

    }

    ~PCQueue(){
	    pthread_mutex_destroy(&loby_lock);
        pthread_mutex_destroy(&vip_lock);
        pthread_cond_destroy(&producer_finished);
        pthread_cond_destroy(&not_empty);
    }

	// Blocks while queue is empty. When queue holds items, allows for a single
	// thread to enter and remove an item from the front of the queue and return it. 
	// Assumes multiple consumers.
	T pop(){
	    //Get in the loby:
        pthread_mutex_lock(&loby_lock);

        //IN THE LOBY::
        while(is_producer_waiting == 1) {
            pthread_cond_wait(&producer_finished, &loby_lock);
        }

        while(q.size() == 0) {
            pthread_cond_wait(&not_empty, &loby_lock);
        }

        pthread_mutex_unlock(&loby_lock);

        //IN VIP ROOM::
        pthread_mutex_lock(&vip_lock);
        T temp = q.front();
        q.pop();
        pthread_mutex_unlock(&vip_lock);


        return temp;
	}

	// Allows for producer to enter with *minimal delay* and push items to back of the queue.
	// Hint for *minimal delay* - Allow the consumers to delay the producer as little as possible.  
	// Assumes single producer 
	void push(const T& item){

        is_producer_waiting = 1;
		pthread_mutex_lock(&vip_lock);

        q.push(item);
        cout << "PUSHED!" ;
        is_producer_waiting = 0;
		pthread_cond_broadcast(&not_empty);

		pthread_mutex_unlock(&vip_lock);

        pthread_cond_broadcast(&producer_finished);
        pthread_cond_broadcast(&not_empty);
	}


private:
	// Add your class memebers here
	pthread_mutex_t loby_lock;
	pthread_mutex_t vip_lock;

	pthread_cond_t not_empty;
	pthread_cond_t producer_finished;

	int is_producer_waiting;
	int producers_count;

	std::queue<T> q;

};
// Recommendation: Use the implementation of the std::queue for this exercise
#endif