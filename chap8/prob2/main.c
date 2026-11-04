#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(void) {
	for (char **ptr = environ; *ptr != NULL; ptr++)
		printf("%s\n", *ptr);
	exit(0);
}
