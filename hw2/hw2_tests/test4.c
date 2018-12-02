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
    pid_t p = fork();
    if(p==0){
         TASSERT( make_changeable(getpid())==0,
        "make_changeable: should return 0 when process is now CS ",__LINE__);
        TASSERT( change(1)==0,"change: should return 0 on success ",__LINE__);
        TASSERT( get_policy(getpid())==1,
        "get_policy: should return 1 when policy enabled ",__LINE__);
        return 0;
    }   
    else{
        busy_wait_by_sec(1);
        TASSERT( get_policy(p)==0,
        "get_policy: should return 0 when policy disabled due to all SC are zombies ",__LINE__);
    } 
    //normal process, policy disabled
    /*fork normal process, then set father as Real time and send waiting for son,
        son should finish first since policy is on, should print the real time after his son
        then all other ascending*/
        FILE* file = fopen("test4.txt","w");
        int j;
    p=fork();
    struct sched_param param;
    param.sched_priority = 99;
    if(p==0){
        TASSERT( make_changeable(getpid())==0,
        "make_changeable: should return 0 when process is now CS ",__LINE__);
        TASSERT( change(1)==0,"change: should return 0 on success ",__LINE__);
        for(j=0;j<100;j++){
            nice(-19);
            pid_t p1=fork();
            if(p1==0){//forked process
                goto print;
            }
            else if(j<50){waitpid(p1,NULL,0);}
        }
    }
    else{
        sched_setscheduler(getpid(), SCHED_RR, & param);
        waitpid(p,NULL,0);
        for(j=0;j<100;j++){
            pid_t p1=fork();
            if(p1!=0){
                goto set_SCHED;
            }
        }
set_SCHED:
if(j<50)
    sched_setscheduler(getpid(), SCHED_RR, & param);
    else{
        nice(20);
        param.sched_priority = 0;
        sched_setscheduler(getpid(), SCHED_OTHER, & param);
    }
    }
print:
    if(get_policy(getpid())!=1){
        fprintf(file,"better prio/real time: %d\n",getpid());
    }
    else 
        fprintf(file,"%d\n",getpid());
    return 0;
}
