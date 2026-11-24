#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *fd1, *fd2;
	int c;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
		exit(1);
	}

	if ((fd1 = fopen(argv[1], "r")) == NULL) {
		exit(1);
	}

	if ((fd2 = fopen(argv[2], "a")) == NULL) {
		fclose(fd1);
		exit(1);
	}

	while ((c = fgetc(fd1)) != EOF) {
		fputc(c, fd2);
	}

	fclose(fd1);
	fclose(fd2);

	return 0;
}
