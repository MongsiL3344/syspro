#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	mode_t mode;

	if (argc != 3) {
		fprintf(stderr, "usage: %s <mode> <file>\n", argv[0]);
		exit(1);
	}

	mode = (mode_t)strtol(argv[1], NULL, 8);
	if (chmod(argv[2], mode) < 0) {
		perror(argv[2]);
		exit(1);
	}

	exit(0);
}
