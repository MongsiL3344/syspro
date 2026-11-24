#include <stdio.h>
#include <unistd.h>

int main(void) {
	int pid;

	pid = fork();
	if (pid == 0) {
		printf("[Child] Hello, world! Pid=%d\n", getpid());
	} else {
		printf("[Parent] Hello, world! Pid=%d\n", getpid());
	}
	return 0;
}
