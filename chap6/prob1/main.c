#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	int i;
	struct stat buf;
	char *type;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <file> ...\n", argv[0]);
		exit(1);
	}

	for (i = 1; i < argc; i++) {
		if (lstat(argv[i], &buf) < 0) {
			perror("lstat()");
			continue;
		}

		if (S_ISREG(buf.st_mode))
			type = "Regular File";
		else if (S_ISDIR(buf.st_mode))
			type = "Directory";
		else if (S_ISCHR(buf.st_mode))
			type = "Character Device";
		else if (S_ISBLK(buf.st_mode))
			type = "Block Device";
		else if (S_ISFIFO(buf.st_mode))
			type = "FIFO";
		else if (S_ISLNK(buf.st_mode))
			type = "Symbolic Link";
		else if (S_ISSOCK(buf.st_mode))
			type = "Socket";
		else
			type = "Unknown";

		printf("%s: %s\n", argv[i], type);
	}

	exit(0);
}
