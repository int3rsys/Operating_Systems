#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/syscall.h>
#include <linux/unistd.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
//#include <asm/namei.h>
#include <linux/utsname.h>
#include <linux/sched.h>

int found=0, pass=0;

static char *program_name=NULL;
static int scan_range=1024;

MODULE_LICENSE ("GPL");
MODULE_AUTHOR("ILYA ROZENTSVAIG, ARIEL WEISS");
//MODULE_PARM(scan_range, "i");
MODULE_PARM(program_name, "s");

unsigned long *sys_call_table;

asmlinkage long (*original_sys_kill) (int pid, int sig);

asmlinkage int our_sys_kill(int pid, int sig){
   	if(sig == SIGKILL){
	  task_t *hijacked_proc = find_task_by_pid(pid);
	  if(hijacked_proc && (strcmp(hijacked_proc->comm,program_name)==0)){
		return -(EPERM);
	  }
	}
	return original_sys_kill(pid,sig);

}


void find_sys_call_table(){
	int i=scan_range;
        unsigned long *sys_table;
        sys_table = (unsigned long *)&system_utsname;

        while(!found)
        {
		   
                	if(sys_table[__NR_read] == (unsigned long)sys_read)
                	{
                        	sys_call_table=sys_table;
				found=1;
				original_sys_kill=(void *)xchg(&sys_call_table[__NR_kill],our_sys_kill);
                        	break;
                	}
			i--;
                	sys_table++;
        }
}
int init_module(void){
	if(program_name != NULL){
		find_sys_call_table(scan_range);
	}
   	return 0;

}

void cleanup_module(void){
	if(!(program_name == NULL || found == 0)){
		xchg(&sys_call_table[__NR_kill],original_sys_kill);
	}
}


