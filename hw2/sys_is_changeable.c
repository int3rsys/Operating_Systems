
#include <linux/kernel.h>
#include <linux/sched.h>

int sys_is_changeable(pid_t pid){
  struct task_struct* proc target_pid = get_task_by_pid(pid);
  if(target_pid == NULL){
    return -ERSCH;
  }
  return target_pid->changeable;
}
