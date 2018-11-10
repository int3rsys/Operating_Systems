//
// Created by Ilya on 10-Nov-18.
//
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <asm/uaccess.h>

struct forbidden_activity_info{
  int syscall_req_level;
  int proc_level;
  int time;
  struct list_head list;
};

int sys_get_process_log(pid_t pid ,int size, struct forbidden_activity_info* user_mem){
    struct task_struct* curr=current;
    printk("[*] Reading log file for process %d: \r\n", pid);
    if (curr == NULL){
        return -1;
    }
    if (curr->is_policy_on == 0){
      return -1;
    }
    if(size == 0){
      return 0;
    }
    if(size > curr->info_list_size){
      return -1;
    }
    // ** Add memory allocation check **

    struct forbidden_activity_info* current_log;
    struct list_head* log_head;
    int cnt=0, result;
    // ** The copy itself: **

    list_for_each(log_head, curr->head){
      current_log = list_entry(log_head,struct forbidden_activity_info, list);
      result = copy_to_user(&user_mem[cnt], current_log, sizeof(struct forbidden_activity_info));
      if (result != 0){
        printk("result is not zero, but: %d\r\n", result);
      }
      printk("#%0d contains: req_level %d, proc level %d, created in %d\n\r",cnt, current_log->syscall_req_level,current_log->proc_level, current_log->time);
      printk("[*] deleting log #%0d\n\r",cnt);
      // FREE HERE
      list_del(&(current_log->list));
      kfree(current_log);
      cnt++;
      if(cnt == size){
        return 0;
      }
    }

    /* Implementation for List

    list_for_each(log_head, curr->head){
      current_log = list_entry(log_head,struct forbidden_activity_info, list);
      printk("#%0d contains: req_level %d, proc level %d, created in %d\n\r",cnt, current_log->syscall_req_level,current_log->proc_level, current_log->time);
      printk("[*] deleting log #%0d\n\r",cnt);
      // FREE HERE
      list_del(&(current_log->list));
      kfree(current_log);
      cnt++;
      if(cnt == size){
        return 0;
      }
    }

    */
    return 0;
}
