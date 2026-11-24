#include <stdio.h>
#include <string.h>

int nflag = 0;
int line = 1;

void print_file(FILE *fp) {
	int c;

	c = getc(fp);
	if (nflag && c != EOF) {
		printf("%6d\t", line++);
	}

	while (c != EOF) {
		putc(c, stdout);

		if (c == '\n') {
			c = getc(fp);
			if (nflag && c != EOF) {
				printf("%6d\t", line++);
			}
		} else {
			c = getc(fp);
		}
	}
}

int main(int argc, char *argv[]) {
	FILE *fp;
	int i = 1;

	if (argc > 1 && strcmp(argv[1], "-n") == 0) {
		nflag = 1;
		i = 2;
	}

	if (i == argc) {
		print_file(stdin);
		return 0;
	}

	for (; i < argc; i++) {
		fp = fopen(argv[i], "r");
		if (fp == NULL) {
			fprintf(stderr, "cat: %s: cannot open file\n", argv[i]);
			continue;
		}

		print_file(fp);
		fclose(fp);
	}

	return 0;
}
