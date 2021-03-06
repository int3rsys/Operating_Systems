//
// Created by Ilya on 08-Nov-18.
//
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>



int sys_enable_policy(pid_t pid ,int size, int password){
    struct task_struct* curr=current;
    struct forbidden_activity_info* empty_log_arr;
    int i=0;
    printk("[*] Turning on policy for pid :%d \n With size: %d, current policy is:%d \r\n", pid, size, curr->is_policy_on);
    if (curr == NULL){
        return -1;
    }
    if (curr->is_policy_on == 1){
      return -1;
    }
    empty_log_arr = kmalloc(sizeof(struct forbidden_activity_info) * curr->array_total_size);
    // INITIALIZE EVERYTHING WITH -1 for debgging purposes.
    for(i;i<size;i++){
      empty_log_arr[i].syscall_req_level=-1;
  		empty_log_arr[i].proc_level=-1;
  		empty_log_arr[i].time=-1;
    }
    if (empty_log_arr == NULL){
      printk("________Memory allocation failed________\r\n");
      return -1;
    }
    curr->log_array=empty_log_arr;
    curr->is_policy_on=1;
    curr->array_total_size=size;
    printk("[*] Policy for %d changed to: %d \r\n", pid, curr->is_policy_on);
    // ** Add memory allocation check **
    /*
    struct forbidden_activity_info* task_activity_log_head;
    task_activity_log_head = kmalloc(sizeof(struct forbidden_activity_info));
    if(task_activity_log_head == NULL){
      printk("________Memory allocation failed________\r\n");
      return -1;
    }
    // setting the head to be 'empty'. Nodes will contain the values.
    task_activity_log_head->syscall_req_level=-1;
    task_activity_log_head->proc_level=-1;
    task_activity_log_head->time=-1;
    INIT_LIST_HEAD(&(task_activity_log_head->list)); // HEAD OF OUR LOG

    curr->head = &(task_activity_log_head->list);
    */
    //struct forbidden_activity_info* temp;
    //temp = list_entry(curr->head,struct forbidden_activity_info, list);

    //printk("[*] Current log head is at %p, contains vals: req_leve %d, level %d and time %d\r\n",curr->head,temp->syscall_req_level, temp->proc_level, temp->time);
    return 0;
}
