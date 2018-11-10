//
// Created by Ilya on 08-Nov-18.
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

int sys_enable_policy(pid_t pid ,int size, int password){
    struct task_struct* curr=current;
    printk("[*] Turning on policy for pid :%d \n With size: %d, current policy is:%d \r\n", pid, size, curr->is_policy_on);
    if (curr == NULL){
        return -1;
    }
    if (curr->is_policy_on == 1){
      return -1;
    }
    // ** Add memory allocation check **

    struct forbidden_activity_info* task_activity_log_head;
    task_activity_log_head = kmalloc(sizeof(struct forbidden_activity_info));
    if(task_activity_log_head == NULL){
      return -1;
    }
    // setting the head to be 'empty'. Nodes will contain the values.
    task_activity_log_head->syscall_req_level=-1;
    task_activity_log_head->proc_level=-1;
    task_activity_log_head->time=-1;
    INIT_LIST_HEAD(&(task_activity_log_head->list)); // HEAD OF OUR LOG

    curr->head = &(task_activity_log_head->list);
    curr->is_policy_on=1;
    curr->info_list_size=size;

    struct forbidden_activity_info* temp;
    temp = list_entry(curr->head,struct forbidden_activity_info, list);

    printk("[*] Policy for %d changed to: %d \r\n", pid, curr->is_policy_on);
    printk("[*] Current log head is at %p, contains vals: req_leve %d, level %d and time %d\r\n",curr->head,temp->syscall_req_level, temp->proc_level, temp->time);
    return 0;
}
