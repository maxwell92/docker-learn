#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>

#define STACK_SIZE (1024 * 1024)

// sync primitive
int checkpoint[2] = {0};
static char child_stack[STACK_SIZE];
char * const child_args[] = {"/bin/bash",NULL};

int child_main(void *args) {
	char c = 'B';
// init sync primitive
	close(checkpoint[1]);
// wait
	read(checkpoint[0],&c,1);
	printf(" - World!  from %d\n",getpid());
/*	printf(" %d %d\n",checkpoint[0],checkpoint[1]);*/
	sethostname("Mushroom",12);
	execv(child_args[0],child_args);
	printf("Ooops!\n");
	return 1;
}

int main() {
// init sync primitive
	pipe(checkpoint);
	printf(" - Hello ?  from %d\n",getpid());
	int child_pid = clone(child_main,child_stack + STACK_SIZE,CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID | SIGCHLD,NULL);
// some damn long init job ...- -!
	sleep(4);
// signal "done"
	close(checkpoint[1]);
	waitpid(child_pid,NULL,0);
/*	printf("%d %d\n",checkpoint[0],checkpoint[1]);*/
	return 0;
}
