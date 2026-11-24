#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXLINE 1024
#define MAXARG 64

void execute(char *cmd) {
	char *args[MAXARG];
	char *token, *saveptr;
	char *infile = NULL;
	char *outfile = NULL;
	int background = 0;
	int argc = 0;
	int pid, status, fd, len;

	token = strtok_r(cmd, " \t\n", &saveptr);
	while (token != NULL && argc < MAXARG - 1) {
		if (strcmp(token, "&") == 0) {
			background = 1;
		} else if (strcmp(token, ">") == 0) {
			outfile = strtok_r(NULL, " \t\n", &saveptr);
		} else if (strcmp(token, "<") == 0) {
			infile = strtok_r(NULL, " \t\n", &saveptr);
		} else {
			args[argc++] = token;
		}
		token = strtok_r(NULL, " \t\n", &saveptr);
	}
	args[argc] = NULL;

	if (argc == 0)
		return;

	len = strlen(args[argc - 1]);
	if (args[argc - 1][len - 1] == '&') {
		args[argc - 1][len - 1] = '\0';
		background = 1;
	}

	fflush(stdout);
	pid = fork();
	if (pid < 0) {
		perror("fork");
		return;
	}

	if (pid == 0) {
		if (infile != NULL) {
			fd = open(infile, O_RDONLY);
			if (fd < 0) {
				perror(infile);
				exit(1);
			}
			dup2(fd, 0);
			close(fd);
		}
		if (outfile != NULL) {
			fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0660);
			if (fd < 0) {
				perror(outfile);
				exit(1);
			}
			dup2(fd, 1);
			close(fd);
		}
		execvp(args[0], args);
		fprintf(stderr, "%s: command not found\n", args[0]);
		exit(127);
	}

	if (background) {
		printf("[%d] background\n", pid);
	} else {
		waitpid(pid, &status, 0);
	}
}

int main(void) {
	char line[MAXLINE];
	char *cmd, *saveptr;
	int status;

	while (1) {
		while (waitpid(-1, &status, WNOHANG) > 0)
			;

		printf("[shell] ");
		fflush(stdout);

		if (fgets(line, MAXLINE, stdin) == NULL)
			break;

		line[strcspn(line, "\n")] = '\0';
		if (strcmp(line, "exit") == 0)
			break;

		cmd = strtok_r(line, ";", &saveptr);
		while (cmd != NULL) {
			execute(cmd);
			cmd = strtok_r(NULL, ";", &saveptr);
		}
	}

	return 0;
}
