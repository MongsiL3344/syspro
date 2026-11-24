#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXARG 64
#define MAXLINE 1024

int main(void) {
	char line[MAXLINE];
	char *args[MAXARG];
	char *token, *saveptr;
	int pid, child, status;
	int argc, background, len;

	while (1) {
		while ((child = waitpid(-1, &status, WNOHANG)) > 0)
			printf("[%d] child process end %d\n", getpid(), child);

		printf("Pls input cmd : ");
		fflush(stdout);

		if (fgets(line, MAXLINE, stdin) == NULL) {
			printf("Parent process end\n");
			printf("Exit\n");
			break;
		}

		argc = 0;
		token = strtok_r(line, " \t\n", &saveptr);
		while (token != NULL && argc < MAXARG - 1) {
			args[argc++] = token;
			token = strtok_r(NULL, " \t\n", &saveptr);
		}
		args[argc] = NULL;

		if (argc == 0)
			continue;

		if (argc == 1 && strcmp(args[0], "exit") == 0) {
			printf("Parent process end\n");
			printf("Exit\n");
			break;
		}

		background = 0;
		len = strlen(args[argc - 1]);
		if (strcmp(args[argc - 1], "&") == 0) {
			background = 1;
			args[--argc] = NULL;
		} else if (args[argc - 1][len - 1] == '&') {
			background = 1;
			args[argc - 1][len - 1] = '\0';
		}

		if (argc == 0)
			continue;

		printf("[%d] Parent process start\n", getpid());
		fflush(stdout);

		pid = fork();
		if (pid < 0) {
			perror("fork");
			continue;
		}

		if (pid == 0) {
			if (background) {
				printf("[%d] child process start\n", getpid());
				fflush(stdout);
			}
			execvp(args[0], args);
			fprintf(stderr, "%s: command not found\n", args[0]);
			exit(127);
		}

		if (!background) {
			child = waitpid(pid, &status, 0);
			if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
				printf("SUCCESS\n\n");
			else
				printf("FAIL\n\n");
		}
	}

	return 0;
}
