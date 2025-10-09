#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFSIZE 1024

int main(int argc, char *argv[])
{
	int fd;
	char buf;
	char savedText[10][100];
	int row = 0, col = 0;
	long total = 0;
	
	if ((fd = open(argv[1], O_RDONLY)) == -1) {
		perror(argv[1]);
		exit(1);
	}

	while (read(fd, &buf, 1) > 0) {
		savedText[row][col] = buf;
		if (buf == '\n') {
			savedText[row++][col] = '\0';
			col = 0;
		}
		else
			col++;
	}
	
	if (col > 0) {
		savedText[row][col] = '\0';
		row++;
	}
	close(fd);
	printf("File read success\n");
	printf("Total Line : %d\n", row);
	printf("You can choose 1 ~ %d Line\n", row);
	printf("Pls 'Enter' the line to select : ");

	char line[10] = {0};
	scanf("%s", line);
	int num1, num2;
	if (line [1] == '-') {
		num1 = line[0] - '0';
		num2 = line[2] - '0';
		for (int i = num1; i <= num2; i++) {
			printf("%s\n", savedText[i - 1]);
		}
	}
	else if (line[1] == ',') {
		num1 = line[0] - '0';
		num2 = line[2] - '0';
		for (int i = 1; i <= 4; i++) {
			if (num1 == i)
				printf("%s\n", savedText[i - 1]);
			if (num2 == i)
				printf("%s\n", savedText[i - 1]);
		}
	}
	else if (line [0] == '*') {
		for (int i = 0; i <= 3; i++) 
			printf("%s\n", savedText[i]);
	}
	else {
		num1 = line[0] - '0';
		for (int i = 1; i <= 4; i++) {
			if (num1 == i)
				printf("%s\n", savedText[i - 1]);
		}
	}
	exit(0);
}
