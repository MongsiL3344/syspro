#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	DIR *dp;
	struct dirent *d;

	if (argc != 2) {
		fprintf(stderr, "usage: %s <dir>\n", argv[0]);
		exit(1);
	}

	dp = opendir(argv[1]);
	if (dp == NULL) {
		perror(argv[1]);
		exit(1);
	}

	while ((d = readdir(dp)) != NULL)
		printf("%s %lu\n", d->d_name, (unsigned long)d->d_ino);

	closedir(dp);
	exit(0);
}
