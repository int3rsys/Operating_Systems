#include <errno.h>
#include <sched.h>
#include "hw2_syscalls.h"
#include <sys/types.h>
#include <unistd.h>
#include "stdio.h"
#include "assert.h"
#include "stdio.h"
#include "test.h"
int main(){
    int i;
    FILE* file = fopen("test2.txt","w");
      assert(change(1)==0);
     pid_t p = fork();
     if(p==0){
         assert(make_changeable(getpid())==0);
         assert(change(1)==0);
         for(i=0;i<10;i++){
             fork();
         }
     }
     else{
         for(i=0;i<10;i++){
             fork();
         }
     }
     if(get_policy(getpid())==1)
          fprintf(file,"%d\n",getpid());
    return 0;
}
