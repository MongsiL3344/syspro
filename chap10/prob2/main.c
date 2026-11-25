#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
	int id;
	char name[20];
	struct student *next;
};

int main(void) {
	struct student *head = NULL, *ptr;
	int id, count = 0;
	char name[20];

	printf("학번과 이름을 입력하세요\n");
	while (scanf("%d %19s", &id, name) == 2) {
		ptr = (struct student *)malloc(sizeof(struct student));
		if (ptr == NULL) {
			perror("malloc");
			exit(1);
		}
		ptr->id = id;
		strcpy(ptr->name, name);
		ptr->next = head;
		head = ptr;
	}

	printf("\n* 학생 정보(역순) *\n");
	while (head != NULL) {
		ptr = head;
		printf("학번: %d 이름: %s\n", ptr->id, ptr->name);
		head = ptr->next;
		free(ptr);
		count++;
	}
	printf("총 %d 명입니다.\n", count);

	return 0;
}
