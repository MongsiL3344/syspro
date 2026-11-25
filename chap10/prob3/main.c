#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char str[32] = "Do you like Linux?";
	char *ptr, *p;

	ptr = (char *)malloc(32);
	if (ptr == NULL) {
		perror("malloc");
		exit(1);
	}

	/*
	 * str에서 strlen(str) + 1바이트를 ptr로 복사
	 * dst의 주소를 반환
	 */
	memcpy(ptr, str, strlen(str) + 1);
	puts(ptr);

	/*
	 * ptr부터 1바이트를 'l'로 채움
	 * ptr의 주소를 반환
	 */
	memset(ptr + 12, 'l', 1);
	puts(ptr);

	/*
	 * ptr부터 strlen(ptr)바이트 안에서 'l'이 처음 나오는 위치를 탐색
	 * 찾으면 그 주소 반환, 없으면 NULL을 반환
	 */
	p = (char *)memchr(ptr, 'l', strlen(ptr));
	puts(p);

	/*
	 * str+7에서 10바이트를 str+12로 복사
	 * dst의 주소를 반환
	 */
	memmove(str + 12, str + 7, 10);
	puts(str);

	free(ptr);
	return 0;
}
