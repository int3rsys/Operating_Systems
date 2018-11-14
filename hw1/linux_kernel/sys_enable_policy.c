
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <asm/uaccess.h>



int sys_enable_policy(pid_t pid ,int size, int password){
	if(pid < 0) return -ESRCH;
	
	struct task_struct* proc = find_task_by_pid(pid);
    struct forbidden_activity_info* empty_log_arr;
    int i=0;
	
	if(pid < 0 || proc == NULL){
      return -ESRCH;
    }
    if(proc->is_policy_on || password != 234123 || size < 0){
      return -EINVAL;
    }
	
    printk("[*] Turning on policy for pid :%d \n With size: %d, current policy is:%d \r\n", pid, size, proc->is_policy_on);

    empty_log_arr = kmalloc(sizeof(struct forbidden_activity_info) * size, GFP_KERNEL );
    if (empty_log_arr == NULL){
      printk("________Memory allocation failed________\r\n");
      return -EINVAL;
    }
	// INITIALIZE EVERYTHING WITH -1 for debgging purposes.
    for( ; i < size ;i++){
        empty_log_arr[i].syscall_req_level=-1;
  		empty_log_arr[i].proc_level=-1;
  		empty_log_arr[i].time=-1;
    }
	// CHANGE THE PCB:
    proc->log_array = empty_log_arr;
    proc->is_policy_on = POLICY_ON;
    proc->array_total_size = size;
    printk("[*] Policy for %d changed to: %d \r\n", pid, proc->is_policy_on);
    
	return 0;
}
