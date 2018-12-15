//
// Created by Ilya on 15-Dec-18.
//
#include "Semaphore.hpp"
#include <ostream>
#include <time.h>

Semaphore s;

void *try_up(void *args) {
    char *msg =(char*)args;
    cout << msg << " is here! My id is: " << pthread_self() << endl;
    s.up();
    return NULL;
}

void *try_down(void *args) {
    char *msg =(char*)args;
    cout << msg << " is here! My id is: " << pthread_self() << endl;
    s.down();
    return NULL;
}

int main() {
    s=Semaphore();
    pthread_t t1, t2,t3,t4,t5,t6,t7;
    const char *m1 = "Thread num 1";
    const char *m2 = "Thread num 2";
    const char *m3 = "Thread num 3";
    const char *m4 = "Thread num 4";
    const char *m5 = "Thread num 5";
    const char *m6 = "Thread num 6";
    const char *m7 = "Thread num 7";
    pthread_create(&t2, NULL, try_down, (void *) m1);
    pthread_create(&t1, NULL, try_down, (void *) m2);
    pthread_create(&t3, NULL, try_down, (void *) m3);
    sleep(1);
    pthread_create(&t4, NULL, try_up, (void *) m4);
    pthread_create(&t5, NULL, try_up, (void *) m5);
    pthread_create(&t6, NULL, try_up, (void *) m6);
    pthread_create(&t7, NULL, try_up, (void *) m7);
    pthread_join(t1, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t2, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);
    pthread_join(t7, NULL);
    return 0;
}
