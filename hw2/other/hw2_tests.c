#include <unistd.h>
#include <sys/wait.h>

#include "hw2_syscalls.h"

#define HW2_POLICY_ON 1
#define HW2_POLICY_OFF 0



/*
 * Tests the is_changeable syscall
 */
void test_is_changeable(){
    printf("<<======:::::IS CHANGEABLE TEST:::::=====>> \n");
    pid_t pid1 = getpid();
    int ret;

    // ret should be 0:
    ret = is_changeable(pid1);
    printf("ret should be 0:  %d \n",ret);
    // ret should be 0:
    ret = make_changeable(pid1);
    printf("ret should be 0:  %d \n",ret);
    // ret should be 1
    ret = is_changeable(pid1);
    printf("ret should be 1:  %d \n",ret);
    
}
/*
 * Tests the make_changeable syscall
 * 3 processes: father   - OTHER
 *              son      - CHANGEABLE
 *              grandson - CHANGEABLE
 * [check fork & syscalls errors]
 * TODO: check errno vals.
 */
void test_make_changeable(){
    int ret;
    printf("<<======:::::MAKE CHANGEABLE TEST:::::=====>> \n");
    printf("Father PID:  %d \n",getpid());
    
    pid_t pid2 = fork();//father and son are OTHER

    //son code:
    if(pid2 == 0){
        //make son CHANGEABLE:
        ret = make_changeable(getpid());//success
        printf("[%d]>> ret should be 0:  %d \n",getpid(),ret);

        fork(); //grandson should derive the policy 
        wait(NULL);
        ret = is_changeable(getpid());//success x2
        printf("[%d]>> TWISE: ret should be 1:  %d \n",getpid(),ret);
        //make sure can't make CHANGEABLE twice:
        ret = make_changeable(getpid());//fail
        printf("[%d]>> TWISE: ret should be -1:  %d \n",getpid(),ret);

        return;
    }

    wait(NULL);
    //father stays OTHER:
    ret = is_changeable(getpid());
    printf("[%d]>> ret should be 0:  %d \n",getpid(),ret);

}
/*
 * Tests the change syscall
 * 2 processes: father   - OTHER
 *              son      - CHANGEABLE
 * [check regular behavior & syscalls errors]
 * TODO: check errno vals.
 */
void test_change(){
    printf("<<======:::::CHANGE TEST:::::=====>> \n");
    int ret;
    printf("Father PID:  %d \n",getpid());
    
    pid_t pid2 = fork();//father and son are OTHER

    //son code:
    if(pid2 == 0){
        //make son CHANGEABLE:
        ret = make_changeable(getpid());//success
        printf("[%d]>> ret should be 0:  %d \n",getpid(),ret);
        
        ret = get_policy(getpid());//policy disable: ret=0
        printf("[%d]>> ret should be 0:  %d \n",getpid(),ret);
        
        //turn policy ON:
        ret = change(HW2_POLICY_ON);//policy should turn on
        printf("[%d]>> ret should be 0:  %d \n",getpid(),ret);

        ret = get_policy(getpid());//policy enable: ret=1
        printf("[%d]>> ret should be 1:  %d \n",getpid(),ret);

        //turn policy OFF:
        ret = change(HW2_POLICY_OFF);//policy should turn off
        printf("[%d]>> ret should be 0:  %d \n",getpid(),ret);

        ret = get_policy(getpid());//policy disable: ret=0
        printf("[%d]>> ret should be 0:  %d \n",getpid(),ret);

        return;
    }

    wait(NULL);

}
/*
 * Tests the get_policy syscall
 */
void test_get_policy(){

}
/*
 * Policy Test 01:
 * 2 SC processes
 * 1 OTHER with high priority
 * 
 */
void test_make_changeable_preempted(){
    int ret, i = 0;
    //int stat;
    pid_t pid, father = getpid();
    pid_t pids[3]; 
    printf("<<======:::::MAKE CHANGEABLE PREEMPTED TEST:::::=====>> \n");
    printf("Father PID:  %d \n",getpid());
    
    ret = change(HW2_POLICY_ON);
    printf("Change: ret should be 0:  %d \n",ret);

    ret = make_changeable(getpid()); //make it changeable!
    printf("[%d]>> ret should be 0:  %d \n",getpid(),ret); 

    while(i<2){
        pid = fork();
        if(pid != 0)//if father, break
            break;
        //enter son into the array: 
        pids[i] = getpid();
        printf(">>Add [%d] to the array. \n",getpid());
        i++;
    }
    wait(NULL);
    
//Now there are: 2 CHANGEABLEs , 1 OTHER
//father < pid[0] < pid[1] 
    //
    if(getpid() == pids[0]){

    }else if (getpid() == pids[1]){

    }else{//father

    }
    printf("[%d] went to sleep. \n",getpid());
        sleep(10);
    printf("[%d] now running. \n",getpid());
        waitpid(pids[0],NULL,WNOHANG);//wake first son
    printf("[%d] >>now running. \n",getpid()); 
    //}
    //sched_yield();
    sleep(2);
    wait(NULL);
}
/*
 * Policy Test 01:
 * 2 SC processes
 * 1 OTHER with high priority
 * 
 */
void test01(){

}

int main(int argc, char const *argv[])
{
    //test_is_changeable();
    //test_make_changeable();
    //test_change();
    test_make_changeable_preempted();
    return 0;
}
