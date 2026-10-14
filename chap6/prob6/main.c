#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "usage: %s <original> <link>\n", argv[0]);
		exit(1);
	}

	if (link(argv[1], argv[2]) == -1) {
		perror(argv[1]);
		exit(1);
	}

	exit(0);
}
