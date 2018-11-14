
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <asm/uaccess.h>


int sys_get_process_log(pid_t pid ,int size, struct forbidden_activity_info* user_mem){
	if(pid < 0) return -ESRCH;
	
    struct task_struct* proc = find_task_by_pid(pid);
    struct forbidden_activity_info* new_arr;
    int i = 0,j = 0, result;
    printk("[*] Reading log file for process %d: \r\n", pid);

	if(pid < 0 || proc == NULL){
      return -ESRCH;
    }
    if(proc->is_policy_on == POLICY_OFF || size > proc->curr_size || size < 0){
      return -EINVAL;
    }

    // ** The copy itself: **
	result = copy_to_user(user_mem , proc->log_array, (sizeof(struct forbidden_activity_info) * size) );

	if (result != 0){
        printk("__FAILED TO COPY TO USER with pid %d\r\n", result);
        return -EINVAL;
    }
	
	
    printk("+++++ Copied %d records ++++++\r\n",size);
    // MOVE old records to the beginning
    new_arr = kmalloc(sizeof(struct forbidden_activity_info) * proc->array_total_size, GFP_KERNEL);
    if (!new_arr){
        printk("__FAILED TO KMALLOC NEW ARRAY\n");
        return -EINVAL;
    }
	// if time (or any other param) == -1, then we don't need to copy these vals. We set them anyways below
    proc->curr_size = (proc->array_total_size - size);
	i = size;
	//COPY THE REMAINING LOGS INTO THE NEW ARRAY:
	for( ; i < proc->array_total_size ; i++){
        new_arr[j].syscall_req_level = proc->log_array[i].syscall_req_level;
        new_arr[j].proc_level = proc->log_array[i].proc_level;
        new_arr[j].time = proc->log_array[i].time;
		j++;
      }
		
    kfree(proc->log_array);
    proc->log_array = new_arr;
    return 0;
}
