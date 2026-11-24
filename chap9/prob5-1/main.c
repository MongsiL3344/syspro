#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int fd;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(1);
	}

	fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0660);
	if (fd == -1) {
		perror("open");
		exit(1);
	}

	dup2(fd, 1);
	close(fd);

	printf("Hello stdout !\n");
	fprintf(stderr, "Hello stderr !\n");

	return 0;
}
