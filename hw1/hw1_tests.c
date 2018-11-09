#include "hw1_syscalls.h"
#include <unistd.h>
#include <stdio.h>

/* 
 * fork test1: check simple fork
 * Before the test, set manually the privilege to 1/0 
 */
void fork_test1(){
	//Policy should be enabled on current process:
	enable_policy(getpid() , 1 , 234123);
	//Fork should fail:
	pid_t pid1 = fork();
	if(pid1 == 0){
		printf(" Shouldn't get Here! [%d]\n",pid1);
	}
	wait(NULL);
	printf(" fork_test1: This should be printed ONCE [%d]\n",pid1);
}

/* 
 * fork test2: check a loop of forks
 * Before the test, set manually the privilege to 1/0 
 */
void fork_test2(int num){
	//Policy should be enabled on current process:
	enable_policy(getpid() , 2 , 234123);
	
	pid_t pid1 = -1;
	int i = 0;
	for(i = 0; i < num ; i++){
		//Fork should fail:
		pid1 = fork();
		if(pid1 == 0){
			printf(" Shouldn't get Here! [%d]\n",pid1);
		}
	}
	wait(NULL);
	printf(" fork_test2: This should be printed ONCE [%d]\n",pid1);
	
}

/* 
 * fork test3: check a forks of childes
 * Before the test, set manually the privilege to 1/0 
 */	
void fork_test3(){
	pid_t pid1 = fork();
	//Policy should be enabled on parent, child returns error:
	enable_policy(getpid() , 3 , 234123);
	
	if(getpid() > 0){
		//Fork should fail:
		pid1 = fork();
		if(pid1 == 0){
			printf(" Shouldn't get Here! [%d]\n",pid1);
		}
	}

	wait(NULL);
	printf(" fork_test3: This should be printed TWICE [%d]\n",pid1);
	
}

int main(){
	
	
	/* run ONE test at a time, the process carry on from test to test! */
	
	//fork_test1();
	
	fork_test2(3);
	
	//fork_test3();

	return 0;
}


