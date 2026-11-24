#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char *argv[]) {
	char **ptr;

	switch (argv[1][1]) {
	case 'e':
		if (argc > 2)
			printf("%s = %s\n", argv[2], getenv(argv[2]));
		else
			for (ptr = environ; *ptr != NULL; ptr++)
				printf("%s\n", *ptr);
		break;
	case 'u':
		printf("My Realistic User ID : %d(%s)\n", getuid(),
		       getpwuid(getuid())->pw_name);
		printf("My Valid User ID : %d(%s)\n", geteuid(),
		       getpwuid(geteuid())->pw_name);
		break;
	case 'g':
		printf("My Realistic Group ID : %d(%s)\n", getgid(),
		       getgrgid(getgid())->gr_name);
		printf("My Valid Group ID : %d(%s)\n", getegid(),
		       getgrgid(getegid())->gr_name);
		break;
	case 'i':
		printf("my process number : [%d]\n", getpid());
		break;
	case 'p':
		printf("my parent's process number : [%d]\n", getppid());
		break;
	}

	return 0;
}
