//#include <linux/sched.h>
#include <linux/errno.h>
#include <linux/unistd.h>
#include <sys/types.h>



struct forbidden_activity_info{
  int syscall_req_level;
  int proc_level;
  int time;
};

int enable_policy(pid_t pid ,int size, int password){
   int res;

    __asm__(
    "int $0x80;"
    : "=a" (res)
    : "0" (243), "b"(pid), "c"(size),"d"(password)
    );
    if ((res) < 0){
      errno = -(res);
      res = -1;
    }
    return res;
}

int disable_policy(pid_t pid, int password){
  int res;

  __asm__(
  "int $0x80;"
  : "=a" (res)
  : "0" (244), "b"(pid), "c"(password)
  );
    if ((res) < 0){
      errno = -res;
      res = -1;
    }
    return res;
}

int set_process_capabilities(pid_t pid,int new_level, int password){
  int res;

  __asm__(
  "int $0x80;"
  : "=a" (res)
  : "0" (245), "b"(pid), "c"(new_level), "d"(password)
  );
    if ((res) < 0){
      errno = -res;
      res = -1;
    }
    return res;
}

int get_process_log(pid_t pid, int size, struct forbidden_activity_info* user_mem){
  int res;

  __asm__(
  "int $0x80;"
  : "=a" (res)
  : "0" (246), "b"(pid), "c"(size), "d"(user_mem)
  );
    if ((res) < 0){
      errno = -res;
      res = -1;
    }
    return res;
}
