//
// Created by Ilya on 10-Nov-18.
//
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <asm/uaccess.h>


int sys_get_process_log(pid_t pid ,int size, struct forbidden_activity_info* user_mem){
    struct task_struct* curr=current;
    struct forbidden_activity_info* current_log;
    struct forbidden_activity_info* new_arr;
    int i=0, result,i2=0;
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
    if(size > curr->curr_size){
      printk("___________Size (%d) given is bigger than amount of records(%d)!___________\r\n",size,curr->curr_size);
      return -1;
    }
    // ** The copy itself: **

    for(i;i<size;i++){
      result = copy_to_user(&user_mem[i],&(curr->log_array[i]), sizeof(struct forbidden_activity_info));
      if (result != 0){
        printk("__FAILED TO COPY TO USER with pid %d\r\n", result);
        return -1;
      }
    }

    printk("+++++ Copied %d records ++++++\r\n",i);
    // MOVE old records to the beginning
    new_arr = kmalloc(sizeof(struct forbidden_activity_info) * curr->array_total_size);
    // if time (or any other param) == -1, then we don't need to copy these vals. We set them anyways below
    if (curr->log_array[i].time == -1){
      for(i2;i2<curr->array_total_size; i2++){
        new_arr[i2].syscall_req_level = -1;
        new_arr[i2].proc_level = -1;
        new_arr[i2].time = -1;
      }
      i=0;
    }else{
      for(i;i<curr->curr_size;i++){
        new_arr[i2].syscall_req_level = curr->log_array[i].syscall_req_level;
        new_arr[i2].proc_level = curr->log_array[i].proc_level;
        new_arr[i2].time = curr->log_array[i].time;
        i2++;
      }
      for(i2;i2<curr->array_total_size; i2++){
        new_arr[i2].syscall_req_level = -1;
        new_arr[i2].proc_level = -1;
        new_arr[i2].time = -1;
      }
    }

    kfree(curr->log_array);
    curr->curr_size = i;
    curr->log_array=new_arr;
    return 0;
}
