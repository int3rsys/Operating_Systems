//#include "Semaphore.hpp"
#include "PCQueue.hpp"
#include <ostream>
#include <time.h>

PCQueue<int> p;
//Semaphore s;
/*
void *try_up(void *args) {
    char *msg =(char*)args;
    //int* pid = (int*)pthread_self().p;
    cout << msg << " is here! My id is: " << pthread_self() << endl;
    s.up();
    return NULL;
}

void *try_down(void *args) {
    char *msg =(char*)args;
    //int* pid = (int*)pthread_self().p;
    cout << msg << " is here! My id is: " << pthread_self() << endl;
    s.down();
    return NULL;
}*/

void *push_it(void *args) {
    //char *msg =(char*)args;
    //int* pid = (int*)pthread_self().p;
    //cout << msg << " is here! My id is: " << pthread_self() << endl;

    p.push(*(int*)args);
    return NULL;
}

void *pop_it(void *args) {
    //char *msg =(char*)args;
    //int* pid = (int*)pthread_self().p;
    //cout << msg << " is here! My id is: " << pthread_self() << endl;
    //cout << p.pop();// << endl;
    p.pop();
    return NULL;
}

int main() {
/*    s=Semaphore();
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
    pthread_join(t7, NULL);*/
    p = PCQueue<int>();
    pthread_t t;
    int i = 0;
    //for( i = 0; i < 7; i++){
       // p.push(i);
    //}
    //sleep(1);
    for( i = 0; i < 70000; i++){
        pthread_create(&t, NULL, pop_it, (void *) &i);
    }
    //i++;
    pthread_create(&t, NULL, push_it, (void *) &i);
    pthread_create(&t, NULL, pop_it, (void *) &i);
    //sleep(1);
    int a=0;
    for( i = 0; i < 70002; i++){
        cout << pthread_join(t, (void**)(&a));

    }



    return 0;
}
