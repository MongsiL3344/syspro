#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#define BUFSIZE 512

int main(int argc, char *argv[]) {
	char buf[BUFSIZE];
	int fd, n, total = 0;

	if ((fd = open(argv[1], O_RDONLY)) == -1) {
		perror(argv[1]);
		return 1;
	}

	while ((n = read(fd, buf, BUFSIZE)) > 0) {
		total += n;
	}

	close(fd);
	printf("%s File size : %d Byte\n", argv[1], total);
	return 0;
}
