
#include <linux/kernel.h>
#include <linux/sched.h>

int sys_is_changeable(pid_t pid){
  struct task_struct* target = find_task_by_pid(pid);
  if(target == NULL){
    return -ERSCH;
  }
  return target->changeable;
}
