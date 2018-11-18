
#include <linux/kernel.h>
#include <linux/sched.h>

int sys_set_process_capabilities(pid_t pid, int new_level, int password){
	if(pid < 0) return -ESRCH;
  struct task_struct* proc = find_task_by_pid(pid);
  if(pid < 0 || proc == NULL){
      return -ESRCH;
    }
    if(proc->is_policy_on == POLICY_OFF || password != 234123 || new_level < 0|| new_level > 2){
      return -EINVAL;
    }
  // DO WE NEED TO CHECK IF CURRENT LEVEL == NEW_LEVEL ??
  // Needs to allocate memory here:
  //printk("[*] Setting a new capability for process %d, from level %d -> to level %d\n", pid, proc->privilege_level, new_level);
	
  proc->privilege_level = new_level;
  return 0;
}
