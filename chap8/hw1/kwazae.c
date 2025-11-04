#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>

int option_e = 0;
int option_u = 0;
int option_g = 0;
int option_i = 0;
int option_p = 0;
int option_H = 0;
int option_S = 0;
int option_P = 0;

int main(int argc, char *argv[])
{
	if (strcmp(argv[1], "-e") == 0)
		option_e = 1;
	else if (strcmp(argv[1], "-u") == 0)
		option_u = 1;
	else if (strcmp(argv[1], "-g") == 0)
		option_g = 1;
	else if (strcmp(argv[1], "-i") == 0)
		option_i = 1;
	else if (strcmp(argv[1], "-p") == 0)
		option_p = 1;

	if ((option_e == 1) && (argc > 2)) {
		if (strcmp(argv[2], "HOME") == 0)
			option_H = 1;
		else if (strcmp(argv[2], "SHELL") == 0)
			option_S = 1;
		else if (strcmp(argv[2], "PATH") == 0)
			option_P = 1;
	}

	if (option_e) {
		if (argc > 2) {
			if (option_H) {
				char *ptr;
				ptr = getenv("HOME");
				printf("HOME = %s \n", ptr);
			}
			if (option_S) {
				char *ptr;
				ptr = getenv("SHELL");
				printf("SHELL = %s \n", ptr);
			}
			if (option_P) {
				char *ptr;
				ptr = getenv("PATH");
				printf("PATH = %s \n", ptr);
			}
		}
		else {
			char **ptr;
			extern char **environ;

			for (ptr = environ; *ptr != 0; ptr++)
				printf("%s \n", *ptr);
			exit(0);
		}
	}

	if (option_u) {
		printf("My Realistc User ID : %d(%s) \n", getuid(), getpwuid(getuid())->pw_name);

	}

	if (option_g) {
		 printf("My Realistic Group ID : %d(%s) \n", getgid(), getgrgid(getgid())->gr_name);
		 printf("My Valid Group ID : %d(%s) \n", getegid(), getgrgid(getegid())->gr_name);
	}

	if (option_i) {
		printf("My process number : [%d] \n", getpid());
	}

	if (option_p) {
		printf("My parent's process number : [%d] \n", getppid());
	}
}
