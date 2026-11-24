#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void validinputnum(int n, int line) {
	if (n < 1 || n > line) {
		printf("숫자 범위 벗어남\n");
		exit(1);
	}
}

int main(int argc, char *argv[]) {
	char savedtext[10][100] = {0};
	char buf, input[100], *token;
	int fd, n, m, i;
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

	printf("File read success\n");
	printf("Total Line : %d\n", line);
	printf("You can choose 1 ~ %d Line\n", line);
	printf("Pls 'Enter' the line to select : ");
	fgets(input, sizeof(input), stdin);

	if (input[0] == '*') {
		for (i = 0; i < line; i++) {
			printf("%d %s\n", i + 1, savedtext[i]);
		}
	} else if (sscanf(input, "%d-%d", &n, &m) == 2) {
		validinputnum(n, line);
		validinputnum(m, line);
		for (i = n; i <= m; i++) {
			printf("%d %s\n", i, savedtext[i - 1]);
		}
	} else {
		for (token = strtok(input, ","); token != NULL;
		     token = strtok(NULL, ",")) {
			n = atoi(token);
			validinputnum(n, line);
			printf("%d %s\n", n, savedtext[n - 1]);
		}
	}

	exit(0);
}
