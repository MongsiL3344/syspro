#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
	int pid, child, status;

	printf("[%d] parental process start\n", getpid());
	pid = fork();
	if (pid == 0) {
		printf("[Child] Hello, world! Pid=%d\n", getpid());
		exit(1);
	}

	child = wait(&status);
	printf("[%d] child process %d end\n", getpid(), child);
	printf("\tend code %d\n", WEXITSTATUS(status));
	return 0;
}
