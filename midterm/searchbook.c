#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "book.h"

int main(int argc, char *argv[])
{
	int fd, count = 0, found = 0;
	int c;
	char search[10];
	struct book record;
	struct book books[10];

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

	do{
		printf("input name of book ) ");	
		scanf("%s", search);
		for (int i = 0; i < count; i++) {
			if (strcmp(search, books[i].bookname) == 0) {
				record = books[i];
				found = 1;
				break;
			}
		}
		if (found) {
			printf("%4s %11s %11s %7s %11s %6s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
			printf("%4d %11s %11s %7d %11d %6s\n", record.id, record.bookname, record.author, record.year, record.numofborrow, (record.borrow ? "True" : "False"));
		}
		else {
			printf("not found book name : '%s'\n", search);
		}
		printf("\n");
		found = 0;
	} while (1);
	close(fd);
	exit(0);
}
