#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

static const char *user_name(uid_t uid) {
	struct passwd *pw = getpwuid(uid);
	return pw ? pw->pw_name : "unknown";
}

static const char *group_name(gid_t gid) {
	struct group *gr = getgrgid(gid);
	return gr ? gr->gr_name : "unknown";
}

int main(void) {
	printf("My Realistic User ID: %d(%s)\n", getuid(), user_name(getuid()));
	printf("My Valid User ID: %d(%s)\n", geteuid(), user_name(geteuid()));
	printf("My Realistic Group ID: %d(%s)\n", getgid(), group_name(getgid()));
	printf("My Valid Group ID: %d(%s)\n", getegid(), group_name(getegid()));
	return 0;
}
