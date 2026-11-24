#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
	int pid1, pid2, child, status;

	printf("[%d] parental process start\n", getpid());
	pid1 = fork();
	if (pid1 == 0) {
		printf("[%d] child process start\n", getpid());
		sleep(1);
		printf("[%d] child process end\n", getpid());
		exit(1);
	}

	pid2 = fork();
	if (pid2 == 0) {
		printf("[%d] child process start\n", getpid());
		sleep(2);
		printf("[%d] child process end\n", getpid());
		exit(2);
	}

	child = wait(&status);
	printf("[%d] child process %d end\n", getpid(), child);
	printf("\tend code %d\n", WEXITSTATUS(status));
	return 0;
}
