#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int fd = open(argv[1], O_RDWR);

	if (fd == -1)
		printf("파일 열기 오류\n");
	else
		printf("file %s success : %d\n", argv[1], fd);

	close(fd);
	return 0;
}
