#include <linux/sched.h>
#include <linux/errno.h>
#include <linux/unistd.h>

int sys_enable_policy(pid_t pid ,int size, int password){
   
    if(pid < 0 ){
        errno = ESRCH;
        return -1;
    }
    if(password != 234123 || size < 0){
        errno = EINVAL;
        return -1;
    }
    task_t* p = find_task_by_pid(pid);
    if(!p){
        errno = ESRCH;
        return -1;
    }
    if(p->is_policy_on){
        errno = EINVAL;
        return -1;
    }
    
    p->is_policy_on = POLICY_ON;
    p->privilege_level = 2;

    return 0;
}
int sys_disable_policy(pid_t pid ,int password){

    return 0;
}
int sys_set_process_capabilities(pid_t pid,int new_level,int password){
    task_t* p = find_task_by_pid(pid);
    if(!p){
        //errno = ESRCH;
        return -1;
    }
    p->privilege_level = new_level;
    return 0;
}

int sys_get_process_log(pid_t pid, int size, struct forbidden_activity_info* user_mem){

    return 0;
}
