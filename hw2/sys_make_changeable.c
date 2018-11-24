
#include <linux/kernel.h>
#include <linux/sched.h>

int sys_make_changeable(pid_t pid){
  struct task_struct* target = find_task_by_pid(pid);

  // NOTE: check case when target==NULL ****

  if(target == NULL){
    return -ESRCH;
  }
  if(current->changeable == 1 || target->changeable == 1){
    return -ESRCH;
  }

  target->changeable=1;
  printk("[*] target(%d) is now a SC process. It's the only one, so global policy is OFF\r\n", pid);
  return 0;
}
