#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "book.h"

int main(int argc, char *argv[])
{
	int fd, count = 0;
	struct book record;
	struct book books[10];
	struct book temp;

	if (argc < 2) {
		fprintf(stderr, "How to use: %s file\n", argv[0]);
		exit(1);
	}
	if ((fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0640)) == -1) {
		perror(argv[1]);
		exit(2);
	}
	printf("%4s %11s %11s %7s %11s %6s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
	while (scanf("%d %s %s %d %d %d", &record.id, record.bookname, record.author, &record.year, &record.numofborrow, &record.borrow) == 6) {
		if (count < 10) {
			books[count] = record;
			count++;
		}
	}
	
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - 1 - i; j++) {
			if (books[j].year < books[j+1].year) {
				temp = books[j];
				books[j] = books[j+1];
				books[j+1] = temp;
			}
		}
	}
	for (int i = 0; i < count; i++) {
		write(fd, (char *) &books[i], sizeof(struct book));
	}
	close(fd);
	exit(0);
}
