compile.sh is a small script that will compile our kernel. reboot after it, if done successfuly.
(don't forget to chmod +x compile.sh)

"list.h" is a userland appilcation of linux/list.h (kernelspace). 

TODO:
1) Create complete tests for every module
2) Check there are no memory leaks
3) Check every process is freed if not called upon 'disable_policy'
4) remove kmalloc from enable_policy, add it separately to every sys_ function 
5) replace list_foreach_safe
6) fix error handling -> check errno
