#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

char type(mode_t mode);
char *perm(mode_t mode);
void printStat(char *file, struct stat *st);

int main(int argc, char *argv[]) {
	DIR *dp;
	char *dir;
	struct stat st;
	struct dirent *d;
	char path[BUFSIZ];

	dir = argc == 1 ? "." : argv[1];

	if ((dp = opendir(dir)) == NULL) {
		perror(dir);
		exit(1);
	}

	while ((d = readdir(dp)) != NULL) {
		snprintf(path, sizeof(path), "%s/%s", dir, d->d_name);
		if (lstat(path, &st) < 0)
			perror(path);
		else
			printStat(d->d_name, &st);
	}

	closedir(dp);
	exit(0);
}

void printStat(char *file, struct stat *st) {
	struct passwd *pw;
	struct group *gr;

	printf("%5ld ", (long)st->st_blocks);
	printf("%c%s ", type(st->st_mode), perm(st->st_mode));
	printf("%3ld ", (long)st->st_nlink);

	pw = getpwuid(st->st_uid);
	if (pw != NULL)
		printf("%s ", pw->pw_name);
	else
		printf("%ld ", (long)st->st_uid);

	gr = getgrgid(st->st_gid);
	if (gr != NULL)
		printf("%s ", gr->gr_name);
	else
		printf("%ld ", (long)st->st_gid);

	printf("%9ld ", (long)st->st_size);
	printf("%.12s ", ctime(&st->st_mtime) + 4);
	printf("%s\n", file);
}

char type(mode_t mode) {
	if (S_ISDIR(mode))
		return 'd';
	if (S_ISREG(mode))
		return '-';
	if (S_ISCHR(mode))
		return 'c';
	if (S_ISBLK(mode))
		return 'b';
	if (S_ISLNK(mode))
		return 'l';
	if (S_ISFIFO(mode))
		return 'p';
	if (S_ISSOCK(mode))
		return 's';
	return '?';
}

char *perm(mode_t mode) {
	static char buf[10];
	int i;

	for (i = 0; i < 9; i++)
		buf[i] = '-';
	buf[9] = '\0';

	for (i = 0; i < 3; i++) {
		if (mode & (S_IRUSR >> (i * 3)))
			buf[i * 3] = 'r';
		if (mode & (S_IWUSR >> (i * 3)))
			buf[i * 3 + 1] = 'w';
		if (mode & (S_IXUSR >> (i * 3)))
			buf[i * 3 + 2] = 'x';
	}
	return buf;
}
