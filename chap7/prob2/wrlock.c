#include "student.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int fd, id;
	struct student record;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(1);
	}
	if ((fd = open(argv[1], O_RDWR)) == -1) {
		perror(argv[1]);
		exit(2);
	}

	printf("\nEnter StudentID you want to modify : ");
	while (scanf("%d", &id) == 1) {
		lseek(fd, (id - START_ID) * sizeof(record), SEEK_SET);
		if (lockf(fd, F_LOCK, sizeof(record)) == -1) {
			perror(argv[1]);
			return -1;
		}
		if (read(fd, &record, sizeof(record)) > 0 && record.id != 0) {
			printf("Name:%s\tStuID:%d\tScore:%d\n", record.name, record.id,
			       record.score);
			printf("Enter new score: ");
			scanf("%d", &record.score);
			lseek(fd, (long)-sizeof(record), SEEK_CUR);
			write(fd, &record, sizeof(record));
		} else
			printf("Record %d not found\n", id);

		lseek(fd, (id - START_ID) * sizeof(record), SEEK_SET);
		lockf(fd, F_ULOCK, sizeof(record));
		printf("\nEnter StudentID you want to modify : ");
	}
	close(fd);
	exit(0);
}
