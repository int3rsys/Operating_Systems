#include "test.h"
#include  <sys/types.h>


int main(){
	int retval;
    int father_pid=getpid();
	TASSERT((retval=is_changeable(father_pid)) == 0,
            "is_changeable: should return 0 (retval=%d)",retval);
	pid_t son_pid = fork();

	if (son_pid == 0)	{
		printf("Test make changeable... ");
		TASSERT((retval=make_changeable(father_pid)) == 0,
			"make_changeable: should return 0 (retval=%d)",retval);
		TASSERT((retval=make_changeable(-1)) == -1,
			"make_changeable: should return -1 (retval=%d)",retval);
		printf("PASSED\n");

		printf("Test is changeable... ");
		TASSERT((retval=is_changeable(father_pid)) == 1,
			"is_changeable: should return 1 (retval=%d)",retval);
		printf("PASSED\n");

		printf("Test change... ");
		TASSERT((retval=change(0)) == 0,
			"change: should return 0 (retval=%d)",retval);
		TASSERT((retval=change(2)) == -1,
			"change: should return -1 (retval=%d)",retval);
		TASSERT((retval=change(1)) == 0,
			"change: should return 0 (retval=%d)",retval);
		printf("PASSED\n");

		printf("Test change... ");
		TASSERT((retval=get_policy(getpid())) == -1,
			"get_policy: should return -1 (retval=%d)",retval);
		TASSERT((retval=get_policy(father_pid)) == 1,
			"get_policy: should return 1 (retval=%d)",retval);
		printf("PASSED\n");
	}

	else	{
		wait(NULL);
			TASSERT((retval=is_changeable(father_pid)) == 1,
				"is_changeable (fork): father #1 check should return 1 (retval=%d)",retval);
		pid_t second_son_pid = fork();
		if (second_son_pid == 0)	{
			printf("Test fork for changeable... ");
			TASSERT((retval=is_changeable(getpid())) == 1,
				"is_changeable (fork): son should return 1 (retval=%d)",retval);
			TASSERT((retval=is_changeable(father_pid)) == 1,
				"is_changeable (fork): father #2 check should return 1 (retval=%d)",retval);
			printf("PASSED\n");
		}
		else	{
		wait(NULL);
		}
		
		printf ("should be printed twice\n");
	}
	return 0;
}


