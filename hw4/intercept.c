#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/syscall.h>
#include <linux/unistd.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/utsname.h>
#include <linux/sched.h>

int found=0, pass=0;

//Default value for program_name is set to NULL
static char *program_name=NULL;
//Default value for scan_range
static int scan_range=1024;

MODULE_LICENSE ("GPL");
MODULE_AUTHOR("ILYA ROZENTSVAIG, ARIEL WEISS");
MODULE_PARM(scan_range, "i"); //scan_range is integer type
MODULE_PARM(program_name, "s"); //program_name is string type

unsigned long *sys_call_table;

//A pointer to our "hijacking" function
asmlinkage long (*original_sys_kill) (int pid, int sig);

asmlinkage int our_sys_kill(int pid, int sig){
   	struct task_struct *hijacked_proc = find_task_by_pid(pid);
   	//The programs name (who received the signal):
	char *hijacked_name=hijacked_proc->comm;
   	if(sig == SIGKILL && (strcmp(hijacked_name, "Bill")==0 || strcmp(hijacked_name,program_name)==0)){
		//printk("We catched the sig\n");
		return -(EPERM);
	}else{
	   	pass=1;
		sys_call_table[__NR_kill]=original_sys_kill;
		sys_kill(pid,sig);
		return 0;
	}

}


void find_sys_call_table(int scan_range){
	int i=scan_range;
        unsigned long *sys_table;
        sys_table = (unsigned long *)&system_utsname;

        while(i)
        {
                if(sys_table[__NR_read] == (unsigned long)sys_read)
                {
                        sys_call_table=sys_table;
                        //printk("Syscall table found at: 0x%p\n",sys_call_table);
                        found=1;
                        original_sys_kill=&sys_call_table[__NR_kill];
                        break;
                }
                i--;
                sys_table++;

        }
}


int init_module(void){
	if(program_name != NULL){
		find_sys_call_table(scan_range);
		if (found!=1){
			printk("System call table wasn't found. Try with a different param\n");  
		}
	}
	sys_call_table[__NR_kill]=our_sys_kill;
   	return 0;

}

void cleanup_module(void){
	if(pass!=1){
	   	sys_call_table[__NR_kill]=original_sys_kill;
		pass=0;
	}
}
