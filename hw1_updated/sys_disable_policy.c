//
// Created by Ilya on 09-Nov-18.
//
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>

struct forbidden_activity_info{
  int syscall_req_level;
  int proc_level;
  int time;
  struct list_head list;
};

int sys_disable_policy(pid_t pid, int password){
    struct task_struct* curr = current;
    printk("[*] Turning policy off for pid :%d, current policy status is: %d \r\n", pid, curr->is_policy_on);
    if (curr == NULL){
        return -1;
    }
    if (curr->is_policy_on == 0){
      return -1;
    }
    // ** Here we delete the log **

    struct forbidden_activity_info* current_log;
    struct list_head* log_head;
    list_for_each(log_head, curr->head){
      current_log = list_entry(log_head,struct forbidden_activity_info, list);
      printk("[*] deleting log with req_level %d, proc level %d, created in %d\n", current_log->syscall_req_level,current_log->proc_level, current_log->time);
      // FREE HERE
      list_del(&(current_log->list));
      kfree(current_log);

    }
    current_log = list_entry(log_head,struct forbidden_activity_info, list);
    printk("[*] deleting log with req_level %d, proc level %d, created in %d\n", current_log->syscall_req_level,current_log->proc_level, current_log->time);
    list_del(&(current_log->list));
    kfree(current_log);
    curr->head=NULL;

    curr->is_policy_on=0;
    printk("[*] Policy for %d changed to: %d \r\n", pid, curr->is_policy_on);
    return 0;

}
