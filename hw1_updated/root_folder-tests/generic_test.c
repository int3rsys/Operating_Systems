#include "hw1_syscalls.h"
//#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>

int main(){
	int result,pid_num;
	int pid=getpid();
  int i=0,*w;
  struct forbidden_activity_info* data;
  result = sys_enable_policy(pid, 10, 234123);
  result = sys_set_process_capabilities(pid,1,234123);
  pid_t new_pid;
	/* Should invoke error: */
  new_pid = fork();
	result = sys_set_process_capabilities(pid,0,234123);
	/* Should invoke error: */
	result = sched_yield();
	/* Should invoke error: */
	result = wait(w);
	data = malloc(sizeof(struct forbidden_activity_info)*4);
	result = sys_get_process_log(pid, 3, data);
	for(i;i<4;i++){
		printf("Removing req_level %d, proc level %d, created in %d\n", data[i].syscall_req_level, data[i].proc_level, data[i].time);
	}
	free(data);

	result = sys_set_process_capabilities(pid,2,234123);
	new_pid = fork();
	/* Let the child complete running */
	result = wait(w);
	/* Don't do anything if child */
	if (new_pid != 0){
		result = sys_set_process_capabilities(pid,1,234123);
		new_pid = fork();
	  result = sys_disable_policy(pid, 234123);
	}
  return 0;
}
