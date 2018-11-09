#include <errno.h>
#include <termios.h>
#include <sys/types.h>


int enable_policy(pid_t pid ,int size, int password){
    int __res;
    __asm__(
        "int $0x80;"
        : "=a" (__res)
        : "0" (243), "b" (pid), "c" (size), "d" (password)
        : "memory"
        );
    if (__res < 0){
        errno = (-__res);
        return -1;
    }

    return __res;

}
