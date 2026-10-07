#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
	int fd1, fd2;

	if ((fd1 = creat("myfile", 0600)) == -1) {
		perror("myfile");
		exit(1);
	}

	write(fd1, "Hello! Linux", strlen("Hello! Linux"));
	fd2 = dup(fd1);
	write(fd2, "Bye! Linux", strlen("Bye! Linux"));

	close(fd1);
	close(fd2);
	return 0;
}
