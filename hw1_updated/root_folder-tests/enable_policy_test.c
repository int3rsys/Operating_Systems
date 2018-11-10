#include "hw1_syscalls.h"
//#include <sys/types.h>
//#include <unistd.h>
//#include <sys/wait.h>

int main(){
	int result,pid_num;
	int pid=getpid();
	int *wstatus;
	//pid_num = wait(wstatus); //should receive error
	result = sys_enable_policy(pid, 10, 234123);
	//pid_num = wait(wstatus); //should be fine
	return result;
}
