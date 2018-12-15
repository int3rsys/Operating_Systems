//
// Created by intersys on 12/15/18.
//
#include <ostream>
#include "Semaphore.hpp"

Semaphore::Semaphore() {
    pthread_mutex_init(&global_lock,NULL);
    pthread_cond_init(&not_empty,NULL);
    cnt=0;
}

Semaphore::Semaphore(unsigned val) {
    pthread_mutex_init(&global_lock,NULL);
    pthread_cond_init(&not_empty,NULL);
    cnt=val;
}

void Semaphore::up() {
    pthread_mutex_lock(&global_lock);
    cnt++;
    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&global_lock);
}

void Semaphore::down() {
    pthread_mutex_lock(&global_lock);
    while(cnt==0){
        pthread_cond_wait(&not_empty,&global_lock);
    }
    cnt--;
    pthread_mutex_unlock(&global_lock);
}

int main(){

    Semaphore s = Semaphore();
    s.up();
    s.down();
    return 0;
}