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
    /* ~~~~~~~~~~~~ Stress tests ~~~~~~~~~~~~~~~ */

        int i;
    for (i = 0; i < 1000000 ; i++) {
        if(i==0){
        TASSERT( is_changeable(getpid()) == 0,
        "Stress tests: is_changeable has failed", __LINE__);
        TASSERT( get_policy(getpid()) == -1,
        "Stress tests: get_policy has failed ", __LINE__);
        TASSERT( errno==EINVAL,
        "Stress tests: get_policy has failed", __LINE__);
    
        TASSERT( make_changeable(getpid()) == 0,
        "Stress tests: make_changeable has failed", __LINE__);
        }
        TASSERT( get_policy(getpid()) == 0,
        "Stress tests: get_policy has failed ", __LINE__);
        TASSERT( change(1) == 0, 
        "Stress tests: change has failed ", __LINE__);
        TASSERT( get_policy(getpid()) == 1,
        "Stress tests: get_policy has failed ", __LINE__);
        TASSERT( change(0) == 0,
        "Stress tests: change has failed ", __LINE__);
        TASSERT( is_changeable(getpid()) == 1,
        "Stress tests: is_changeable has failed ", __LINE__);
    }
    //sc process, policy off
    FILE* file = fopen("test6.txt","w");
    TASSERT( change(1) == 0,
        "Stress tests: change has failed ", __LINE__);
    for(i=0;i<12;i++){
        fork();
    }
        TASSERT( is_changeable(getpid()) == 1,
        "Stress tests: is_changeable has failed ", __LINE__);
        TASSERT( get_policy(getpid()) == 1,
        "Stress tests: get_policy has failed ", __LINE__);
        fprintf(file,"%d\n",getpid());
   // printf("Test 6 passed\n");
}
