#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

int main()
{
	int pid[100];
	int num, child, status, i = 1;
	printf("type num of childs : ");
	scanf("%d", &num);
	for (i = 1; i <= num; i++) {
		pid[i] = fork();
		if (pid[i] == 0) {
			printf("[Child %d] : Started! pid=%d, sleep=%d\n", i - 1, getpid(), i);
			sleep(i);
			printf("[Child %d] : Killed! pid=%d, sleep=%d\n", i - 1, getpid(), i);
			exit(1);
		}
	}
	child = waitpid(pid[num], &status, 0);
	printf("parent killed - last child id = %d\n", child);
}
