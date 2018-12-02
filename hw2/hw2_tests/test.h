#ifndef _TEST_H_
#define _TEST_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <sys/timeb.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <cstdio>
#include <cmath>
#include <iostream>
int test_number = 0;
int tests_passed = 0;

void _print_error(const char *errorName, int lineNumber) {
  printf("\t\t\tTest %2d failed\n", test_number + 1);
  printf(
      "\n***************************************************************************");
  printf("\nError Line: %d\nError description:\n%-80s", lineNumber, errorName);
  printf(
      "\n***************************************************************************\n");
}

void _print_test_number(int line_num) {
  printf("Running test %2d at line number: %3d.", test_number + 1,
         line_num);
}

void TASSERT(bool expression, const char *error_code, int line) {
  if (!expression){
	  _print_test_number(line);
    _print_error(error_code, line);
	exit(1);
}
  else {
    tests_passed += 1;
  }
  test_number += 1;

}

void busy_wait_by_sec(int sec) {
	int passed_sec = 0;
	clock_t before = clock();
	while (passed_sec < sec) {
		 clock_t difference = clock() - before;
		 passed_sec = difference / CLOCKS_PER_SEC;
	}
}
#endif /* _TEST_H_ */
