#include <stdio.h>
#include <signal.h>
#include <sys/types.h>

int main()
{
	int pid[7];
	pid[1] = fork();
	if (pid[1] == 0) {
		printf("Hello\n");
		pid[3] = fork();
		if (pid[3] == 0) {
			printf("Hello\n");
			pid[7] = fork();
			if (pid[7] == 0) {
				printf("Hello\n");
			}
		}
		pid[6] = fork();
		if (pid[6] == 0) {
			printf("Hello\n");
			exit(6);
		}
		exit(1);
	}
	pid[4] = fork();
	if (pid[4] == 0) {
		printf("Hello\n");
		exit(4);
	}
	if (pid[2] == 0) {
		printf("Hello\n");
		pid[5] = fork();
		if (pid[5] == 0) {
			printf("Hello\n");
		}
		exit(2);
	}
	printf("Hello\n");
	return 0;
}
