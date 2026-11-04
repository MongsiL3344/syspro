#include <stdio.h>
#include <stdlib.h>

static void print_env(const char *name) {
	printf("%s = %s\n", name, getenv(name));
}

int main(void) {
	print_env("HOME");
	print_env("SHELL");
	print_env("PATH");
	exit(0);
}
