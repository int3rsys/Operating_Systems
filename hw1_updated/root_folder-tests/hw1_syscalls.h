//#include <linux/sched.h>
#include <linux/errno.h>
#include <linux/unistd.h>
#include <sys/types.h>
#include "list.h"

#define NULL 0

struct forbidden_activity_info{
  int syscall_req_level;
  int proc_level;
  int time;
  struct list_head list;
};

int sys_enable_policy(pid_t pid ,int size, int password){
   int res;
   //int pid=pid;
   //int password=password;
   //int size=size;

   if(pid < 0 ){
      errno = ESRCH;
      return -1;
    }
    if(password != 234123 || size < 0){
      errno = EINVAL;
      return -1;
    }
    if (size < 0){
      return EINVAL;
      return -1;
    }
    __asm__(
    "int $0x80;"
    : "=a" (res)
    : "0" (243), "b"(pid), "c"(size),"d"(password)
    );
    if ((res) < 0){
      errno = EINVAL;
      return -1;
    }
    return 0;
}

int sys_disable_policy(pid_t pid, int password){
  int res;

  if(pid < 0 ){
     errno = ESRCH;
     return -1;
   }
  if(password != 234123){
   errno = EINVAL;
   return -1;
  }
  __asm__(
  "int $0x80;"
  : "=a" (res)
  : "0" (244), "b"(pid), "c"(password)
  );
  if ((res) < 0){
    errno = EINVAL;
    return -1;
  }
  return 0;
}

int sys_set_process_capabilities(pid_t pid,int new_level, int password){
  int res;
  if(pid < 0 ){
     errno = ESRCH;
     return -1;
   }
  if(password != 234123){
   errno = EINVAL;
   return -1;
  }
  if (new_level > 2 || new_level < 0){
    errno = EINVAL;
    return -1;
  }
  __asm__(
  "int $0x80;"
  : "=a" (res)
  : "0" (245), "b"(pid), "c"(new_level), "d"(password)
  );
  if ((res) < 0){
    errno = EINVAL;
    return -1;
  }
  return 0;
}

int sys_get_process_log(pid_t pid, int size, struct forbidden_activity_info* user_mem){
  int res;
  if(pid < 0 ){
     errno = ESRCH;
     return -1;
  }
  if (user_mem == NULL){
    errno = EINVAL;
    return -1;
  }
  __asm__(
  "int $0x80;"
  : "=a" (res)
  : "0" (246), "b"(pid), "c"(size), "d"(user_mem)
  );
  if ((res) < 0){
    errno = EINVAL;
    return -1;
  }
  return 0;
}
