#include "student.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	struct student rec;
	int fd;

	if (argc != 2) {
		fprintf(stderr, "How to use: %s FileName\n", argv[0]);
		exit(1);
	}
	if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0640)) == -1) {
		perror(argv[1]);
		exit(2);
	}
	printf("%-9s %-7s %-4s\n", "studentID", "Name", "Score");
	while (scanf("%d %s %d", &rec.id, rec.name, &rec.score) == 3) {
		lseek(fd, (long)(rec.id - START_ID) * sizeof(rec), SEEK_SET);
		write(fd, &rec, sizeof(rec));
	}

	close(fd);
	exit(0);
}
