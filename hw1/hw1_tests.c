#include <hw1_syscalls.h>

int main(){
	pid_t pid = fork();
	if (pid > 0) {// parent waits for child
	wait(NULL);
	}
	printf(“who?\n”);
	return 0;
}