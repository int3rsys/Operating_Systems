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
    FILE* file = fopen("test5.txt","w");
    pid_t p = fork();
    if(p==0){
        TASSERT(make_changeable(getpid())==0,
        "make_changeable: should return 0 when process is now CS",__LINE__);
        TASSERT(change(1)==0,"change: should return 0 on success",__LINE__);
        int j;
        for(j=0;j<30;j++){
            pid_t p1=fork();
            if(p1!=0){
                goto out;
            }
        }
        out:
        busy_wait_by_sec(1);
    }
    else{
        int j;
        for(j=0;j<30;j++){
            pid_t p1=fork();
            if(p1!=0){
                goto out1;
            }
        }
        out1:
        nice(20);
        busy_wait_by_sec(1);
    }
    
    if(get_policy(getpid())==1){
    fprintf(file,"%d\n",getpid());
    }
    else
    fprintf(file,"reg: %d\n",getpid());

    return 0;
}
