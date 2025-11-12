#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "book.h"

int main(int argc, char *argv[])
{
	int fd, count = 0;
	int c;
	struct book record;
	struct book books[10];
	struct book temp;

	if (argc < 2) {
		fprintf(stderr, "How to use : %s file\n", argv[0]);
		exit(1);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1) {
		perror(argv[1]);
		exit(2);
	}
	
	while (read(fd, (char *)&record, sizeof(record)) > 0) {
		if (count < 5) {
			books[count] = record;
			count++;
		}
	}

	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - 1 - i; j++) {
			if (books[j].numofborrow < books[j+1].numofborrow) {
				temp = books[j];
				books[j] = books[j+1];
				books[j+1] = temp;
			}
		}
	}

	printf("--bookquery--\n");
	do{
		printf("0: list of all books, 1: list of available books ) ");
		scanf ("%d", &c);
		printf("%4s %11s %11s %7s %11s %6s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
		lseek(fd, 0L, SEEK_SET);
		for (int i = 0; i < count; i++) {
			record = books[i];
			if (c == 0) {
				printf("%4d %11s %11s %7d %11d %6s\n", record.id, record.bookname, record.author, record.year, record.numofborrow, (record.borrow ? "True" : "False"));
			}
			if (c == 1) {
				if (record.borrow == 1) {
					printf("%4d %11s %11s %7d %11d %6s\n", record.id, record.bookname, record.author, record.year, record.numofborrow, (record.borrow ? "True" : "False"));
				}
			}
		}
		printf("\n");
	} while (1);
	close(fd);
	exit(0);
}
