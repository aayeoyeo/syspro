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
	
	for (int i = row - 1; i >= 0; i--)
		printf("%s\n", savedText[i]);

	exit(0);
}
