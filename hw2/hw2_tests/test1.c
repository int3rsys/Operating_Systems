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
    TASSERT(change(0)==0,
        "change: should return 0 when input is 0",__LINE__);
    TASSERT( change(1)==0,
        "change: should return 0 when input is 1",__LINE__);
      TASSERT( change(2)==-1,
        "change: should return -1 when input is 2",__LINE__);
             TASSERT( errno==EINVAL,
    "change: errno should return EINVAL when change input incorrect",__LINE__);
    TASSERT( get_policy(getpid())==-1,
        "get_policy: should return -1 when process isn't SC",__LINE__);
             TASSERT( errno==EINVAL,
    "get_policy: errno should return EINVAL when target process isn't SC",__LINE__);
    TASSERT(get_policy(-1)==-1,
        "get_policy: should return -1 when process does not exists",__LINE__);
             TASSERT( errno==ESRCH,
    "get_policy: errno should return ESRCH when process does not exists",__LINE__);  
    //test is_changeable
     TASSERT( is_changeable(getpid())==0,
    "is_changeable: should return 0 when process is not CS",__LINE__);
    TASSERT( is_changeable(-1)==-1,
    "is_changeable: should return -1 when process does not exists",__LINE__);
    TASSERT( errno==ESRCH,
    "is_changeable: errno should return ESRCH when process is not exists",__LINE__);
    //test make_changeable
    TASSERT( make_changeable(-1)==-1,
    "make_changeable: should return -1 when process does not exists",__LINE__);
      TASSERT( errno==ESRCH,
    "make_changeable: errno should return ESRCH when process does not exists",__LINE__);
    
    pid_t p =fork();
    if(p==0){
        TASSERT( make_changeable(getpid())==0,
        "make_changeable: should return 0 when process is now CS",__LINE__);
        TASSERT( get_policy(getpid())==0,
        "get_policy: should return 0 when policy disabled (there were 0 CS at enable)",__LINE__);
        TASSERT( make_changeable(getpid())==-1,
    "make_changeable: should return -1 when process is already CS",__LINE__);
     TASSERT( errno==EINVAL,
    "make_changeable: errno should return EINVAL when process is already SC",__LINE__);
        TASSERT( make_changeable(getppid())==-1,
    "make_changeable: should return -1 when target process is already CS",__LINE__);
     TASSERT( errno==EINVAL,
    "make_changeable: errno should return EINVAL when target process is already SC",__LINE__);
        return 0;
    }
    else{
        wait(NULL);
    }
    p=fork();
    if(p==0){
        TASSERT( make_changeable(getppid())==0,
        "make_changeable: should return 0 when process is now CS",__LINE__);
         struct sched_param param;
    param.sched_priority = 99;
    sched_setscheduler(getpid(), SCHED_RR, & param);
     TASSERT( make_changeable(getpid())==-1,
    "make_changeable: should return -1 when process is real time",__LINE__);
        return 0;
    }
    else{
        wait(NULL);
        TASSERT( make_changeable(1)==-1,
        "make_changeable: should return -1 when calling process is already CS",__LINE__);
        TASSERT( errno==EINVAL,
    "make_changeable: errno should return EINVAL when calling process is already SC",__LINE__);
    }
    //cs process
      TASSERT( change(1)==0,
        "change: should return 0 when input is 1",__LINE__);
TASSERT( get_policy(getpid())==1,
        "get_policy: should return 1 when policy enabled",__LINE__);
        TASSERT( is_changeable(getpid())==1,
    "is_changeable: should return 1 when process is CS",__LINE__);
   p=fork();
   if(p==0){
       TASSERT( is_changeable(getpid())==1,
    "is_changeable: should return 1 when process is CS",__LINE__);
    TASSERT( get_policy(getpid())==1,
        "get_policy: should return 1 when policy enabled",__LINE__);
        return 0;
   }
   else{
       wait(NULL);
       TASSERT( get_policy(getpid())==1,
        "get_policy: should return 1 when policy enabled",__LINE__);
        TASSERT( change(0)==0,
        "change: should return 0 when input is 0",__LINE__);
        TASSERT( get_policy(getpid())==0,
        "get_policy: should return 0 when policy enabled",__LINE__);
   }
    printf("Test 1 passed\n");
    return 0;
}
