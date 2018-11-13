//
// Created by Ilya on 09-Nov-18.
//
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>

int sys_disable_policy(pid_t pid, int password){
    struct task_struct* curr = current;
    struct forbidden_activity_info* current_log;
    int i=0;
    if (curr == NULL){
        return -1;
    }
    if (curr->is_policy_on == 0){
      return -1;
    }
    printk("[*] Turning policy off for pid :%d \r\n", pid);
    // ** Here we delete the log **
    if(curr->log_array != NULL){
      printk("__Clearing %d's logs__\r\n", curr->pid);
        for(i;i<curr->array_total_size;i++){
          printk("\t[*] deleting log with req_level %d, proc level %d, created in %d\n", curr->log_array[i].syscall_req_level,curr->log_array[i].proc_level,curr->log_array[i].time);
        }
    }
    kfree(curr->log_array);
    curr->log_array=NULL;
    curr->is_policy_on=0;
    printk("[*] Policy for %d changed to: %d \r\n", pid, curr->is_policy_on);
    return 0;

}
