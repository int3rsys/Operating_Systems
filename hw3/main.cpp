//
// Created by Ilya on 15-Dec-18.
//
#include "Semaphore.hpp"
#include <ostream>

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
    pthread_t t1, t2;
    const char *m1 = "Thread num 1";
    const char *m2 = "Thread num 2";
    pthread_create(&t2, NULL, try_down, (void *) m1);
    pthread_create(&t1, NULL, try_up, (void *) m2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
