#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	struct stat buf;

	if (argc != 3) {
		fprintf(stderr, "usage: %s <target> <linkname>\n", argv[0]);
		exit(1);
	}

	if (stat(argv[1], &buf) == -1) {
		perror(argv[1]);
		exit(1);
	}

	if (symlink(argv[1], argv[2]) == -1) {
		perror(argv[2]);
		exit(1);
	}

	exit(0);
}
