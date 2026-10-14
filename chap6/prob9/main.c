#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	char buffer[1024];
	ssize_t nread;

	if (argc != 2) {
		fprintf(stderr, "usage: %s <link>\n", argv[0]);
		exit(1);
	}

	nread = readlink(argv[1], buffer, sizeof(buffer));
	if (nread < 0) {
		perror("readlink");
		exit(1);
	}

	write(1, buffer, nread);
	exit(0);
}
