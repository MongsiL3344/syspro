#include "student.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	struct student rec;
	int fd, id;
	char c;

	if (argc != 2) {
		fprintf(stderr, "How to use: %s FileName\n", argv[0]);
		return 1;
	}
	if ((fd = open(argv[1], O_RDWR)) == -1) {
		perror(argv[1]);
		return 2;
	}

	do {
		printf("수정할 학생의 학번 입력 : ");
		if (scanf("%d", &id) == 1) {
			lseek(fd, (long)(id - START_ID) * sizeof(rec), SEEK_SET);
			if (read(fd, &rec, sizeof(rec)) > 0 && rec.id != 0) {
				printf("학번:%d\t이름:%s\t점수:%d\n", rec.id, rec.name,
				       rec.score);
				printf("새로운 점수 : ");
				scanf("%d", &rec.score);
				lseek(fd, -(long)sizeof(rec), SEEK_CUR);
				write(fd, &rec, sizeof(rec));
			} else
				printf("레코드 %d 없음\n", id);
		} else {
			printf("입력 오류\n");
			scanf("%*s");
		}
		printf("계속하시겠습니까?(Y/N)");
		scanf(" %c", &c);
	} while (c == 'Y');

	close(fd);
	return 0;
}
