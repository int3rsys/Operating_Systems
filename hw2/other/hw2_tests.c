#include <unistd.h>
#include "hw2_syscalls.h"



/*
 * Tests the is_changeable syscall
 */
void test_is_changeable(){
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
 */
void test_make_changeable(){
    int ret;

    printf("Father PID:  %d \n",getpid());
    
    pid_t pid2 = fork();//father and son are OTHER

    if(pid2 == 0){
        //make son CHANGEABLE:
        ret = make_changeable(getpid());//success
        printf("[%d]>> ret should be 0:  %d \n",getpid(),ret);

        fork(); //grandson should derive the policy 
        ret = is_changeable(getpid());//success x2
        printf("[%d]>> TWISE: ret should be 1:  %d \n",getpid(),ret);
        wait(NULL);
    }
    wait(NULL);
    wait(NULL);
    wait(NULL);
    //father stays OTHER:
    ret = is_changeable(getpid());//fail x2
    printf("[%d]>> ret should be 0:  %d \n",getpid(),ret);

}
/*
 * Tests the change syscall
 */
void test_change(){

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
void test01(){

}

int main(int argc, char const *argv[])
{
    //test_is_changeable();
    test_make_changeable();
    return 0;
}
