#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <getopt.h>

#include "find_min_max.h"
#include "utils.h"

int main( void ) {
	int pid = fork();
    if(pid == 0){
		printf( "This is being printed from the child process\n" );
		execl("sequential_min_max", "sequential_min_max", "1", "10", NULL);
		return 0;
		exit(0);
	} else {
		printf( "This is being printed in the parent process:\n"
		" - the process identifier (pid) of the child is %d\n", pid );
		return 0;
		exit(0);
	}
	return 0;
}
