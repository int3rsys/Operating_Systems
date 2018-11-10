#include "hw1_syscalls.h"
//#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "list.h"

int main(){
	int result,pid_num;
	int pid=getpid();
  int i=0;
  struct forbidden_activity_info* data;
	//pid_num = wait(wstatus); //should receive error
	result = sys_enable_policy(pid, 10, 234123);
  result = sys_set_process_capabilities(pid,1,234123);
  pid_t new_pid;
  new_pid = fork();
  result = sys_set_process_capabilities(pid,0,234123);
  result = wait(NULL);

  printf("Now Reading logfile:\r\n");

  data = malloc(2 *sizeof(struct forbidden_activity_info));
  result = sys_get_process_log(pid, 3, data);
  if(result < 0){
    printf("result=%d\n\r",result);
  }
  printf("Data was copied to: %p\r\n",data->list);
  printf("Finished Reading, now prints copied:\n\r");

  for(i=0;i<2;i++){
    printf("#%d Req Level: %d, Level: %d, Time: %d\n\r", i,data[i].syscall_req_level, data[i].proc_level, data[i].time);
  }

  printf("Logs should be clean now, let's see if we get an error trying to access process log:\n\r");
  result = sys_get_process_log(pid, 3, data);
	if (result == 0){
		printf("Great, no errors!\n\r");
	}else{
		printf("Something bad happend\n\r");
	}

	printf("Let's try to fork:\n\r");
	result = sys_set_process_capabilities(pid,2,234123);
	new_pid=fork();



  result = sys_disable_policy(new_pid, 234123);


	//pid_num = wait(wstatus); //should be fine
	return result;
}
