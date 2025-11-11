#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "book.h"

int main(int argc, char *argv[])
{
	int fd, id;
	int c; 
	struct book record;
	if (argc < 2) {
		fprintf(stderr, "How to use : %s file\n", argv[0]);
		exit(1);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1) {
		perror(argv[1]);
		exit(2);
	}

	printf("--bookquery--\n");
	do{
		printf("0: list of all books, 1: list of available books ) ");
		scanf ("%d", &c);
		printf("%4s %11s %11s %7s %11s %6s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
		lseek(fd, 0L, SEEK_SET);
		while (read(fd, (char *) &record, sizeof(record)) > 0 && record.id != 0) {
			if (c == 0) {
				printf("%4d %11s %11s %7d %11d %6s\n", record.id, record.bookname, record.author, record.year, record.numofborrow, (record.borrow ? "True" : "False"));
			}
			if (c == 1) {
				if (record.borrow == 1) {
					printf("%4d %11s %11s %7d %11d %6s\n", record.id, record.bookname, record.author, record.year, record.numofborrow, (record.borrow ? "True" : "False"));
				}
			}
		}
	} while (1);
	close(fd);
	exit(0);
}
