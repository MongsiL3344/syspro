#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int pid1, child, status;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
		exit(1);
	}

	pid1 = fork();
	if (pid1 == 0) {
		execvp(argv[1], &argv[1]);
		fprintf(stderr, "%s: execution failed\n", argv[1]);
		exit(1);
	} else if (pid1 < 0) {
		perror("fork");
		exit(1);
	}

	child = wait(&status);
	printf("[%d] child process %d end\n", getpid(), child);
	printf("\tend code %d\n", WEXITSTATUS(status));
	return 0;
}
