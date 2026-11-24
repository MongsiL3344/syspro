#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int child, pid, fd, status;

	if (argc < 3) {
		fprintf(stderr, "Usage: %s file command [args...]\n", argv[0]);
		exit(1);
	}

	pid = fork();
	if (pid == 0) {
		fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0660);
		dup2(fd, 1);
		close(fd);
		execvp(argv[2], &argv[2]);
		fprintf(stderr, "%s: execution failed\n", argv[2]);
		exit(1);
	} else {
		child = wait(&status);
		if (WIFEXITED(status))
			printf("[%d] child process %d end\n", getpid(), child);
	}

	return 0;
}
