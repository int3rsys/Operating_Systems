
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

int sys_disable_policy(pid_t pid, int password){
	if(pid < 0) return -ESRCH;
	struct task_struct* proc = find_task_by_pid(pid);
    int i=0;
	
	if(pid < 0 || proc == NULL){
      return -ESRCH;
    }
    if(proc->is_policy_on == POLICY_OFF || password != 234123){
      return -EINVAL;
    }

    //printk("[*] Turning policy off for pid :%d \r\n", pid);
    // ** Here we delete the log **

    //if(proc->log_array != NULL){
    //  printk("__Clearing %d's logs__\r\n", proc->pid);
    //    for( ; i < proc->array_total_size ; i++){
    //      printk("\t[*] deleting log with req_level %d, proc level %d, created in %d\n", proc->log_array[i].syscall_req_level,proc->log_array[i].proc_level,proc->log_array[i].time);
    //    }
    //}

    kfree(proc->log_array);
    proc->log_array = NULL;
    proc->is_policy_on = POLICY_OFF;
	proc->curr_size = 0;
	proc->privilege_level = 2;
    //printk("[*] Policy for %d changed to: %d \r\n", pid, proc->is_policy_on);
	
	
    return 0;

}
