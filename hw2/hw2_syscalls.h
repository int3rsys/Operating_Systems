//#include <linux/sched.h>
#include <linux/errno.h>
#include <linux/unistd.h>
#include <sys/types.h>


int is_changeable(pid_t pid){
   int res;

    __asm__(
    "int $0x80;"
    : "=a" (res)
    : "0" (243), "b"(pid)
    );
    if ((res) < 0){
      errno = -(res);
      res = -1;
    }
    return res;
}

int make_changeable(pid_t pid){
   int res;

    __asm__(
    "int $0x80;"
    : "=a" (res)
    : "0" (244), "b"(pid)
    );
    if ((res) < 0){
      errno = -(res);
      res = -1;
    }
    return res;
}
