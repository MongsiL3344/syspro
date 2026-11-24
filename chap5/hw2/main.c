#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	char savedtext[10][100] = {0};
	char buf;
	int fd, i;
	int line = 0;
	int col = 0;

	fd = open(argv[1], O_RDONLY);

	while (read(fd, &buf, 1) > 0) {
		if (buf == '\n') {
			line++;
			col = 0;
		} else
			savedtext[line][col++] = buf;
	}

	if (col > 0)
		line++;
	close(fd);

	for (i = line - 1; i >= 0; i--) {
		printf("%s\n", savedtext[i]);
	}

	exit(0);
}
