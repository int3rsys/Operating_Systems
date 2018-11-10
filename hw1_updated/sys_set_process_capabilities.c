//
// Created by Ilya on 09-Nov-18.
//
#include <linux/kernel.h>
#include <linux/sched.h>

int sys_set_process_capabilities(pid_t pid, int new_level, int password){
  struct task_struct* curr = current;
  printk("[*] Setting a new capability for process %d, from level %d -> to level %d\n", pid, curr->privilege_level, new_level);
  if (curr == NULL){
    return -1;
  }
  if (curr->is_policy_on==0){
    return 1;
  }
  // DO WE NEED TO CHECK IF CURRENT LEVEL == NEW_LEVEL ??
  // Needs to allocate memory here:

  curr->privilege_level=new_level;
  return 0;
}
