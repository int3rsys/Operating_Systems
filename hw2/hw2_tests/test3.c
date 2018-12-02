#include <errno.h>
#include <sched.h>
#include "hw2_syscalls.h"
#include <sys/types.h>
#include <unistd.h>
#include "stdio.h"
#include "assert.h"
#include "stdio.h"
#include "test.h"
int main(){
    /*creates alot of sc processes, send father waiting (while he has 1 son only)
    therefore biggest pid should finish first*/
    FILE* file = fopen("test3.txt","w");
    TASSERT(make_changeable(getpid())==0,
        "make_changeable: should return 0 when process is now CS",__LINE__);
        TASSERT(change(1)==0,"change: should return 0 on success",__LINE__);
    pid_t p = fork();
    int j=0;
    if(p==0){
        for(j=0;j<1000;j++){
            pid_t p1=fork();
            if(p1!=0){
                wait(NULL);
                goto print;
            }
        }
    }
    else{//father,lower pid
        wait(NULL);
    }
    print:
     fprintf(file,"%d\n",getpid());
     return 0;

}
